#include <arpa/inet.h>

extern "C" {
#include <sai.h>
}

#include "swss/logger.h"
#include "sairedis.h"
#include "meta/saiserialize.h"

#include <map>

#define ASSERT_SUCCESS(format,...) \
    if ((status)!=SAI_STATUS_SUCCESS) \
        SWSS_LOG_THROW(format ": %s", ##__VA_ARGS__, sai_serialize_status(status).c_str());

const char* profile_get_value(
        _In_ sai_switch_profile_id_t profile_id,
        _In_ const char* variable)
{
    SWSS_LOG_ENTER();

    return NULL;
}

int profile_get_next_value(
        _In_ sai_switch_profile_id_t profile_id,
        _Out_ const char** variable,
        _Out_ const char** value)
{
    SWSS_LOG_ENTER();

    if (value == NULL)
    {
        SWSS_LOG_INFO("resetting profile map iterator");

        return 0;
    }

    if (variable == NULL)
    {
        SWSS_LOG_WARN("variable is null");
        return -1;
    }

    SWSS_LOG_INFO("iterator reached end");
    return -1;
}

service_method_table_t test_services = {
    profile_get_value,
    profile_get_next_value
};

void test_sai_initialize()
{
    SWSS_LOG_ENTER();

    // NOTE: this is just testing whether test application will
    // link against libsairedis, this api requires running redis db
    // with enabled unix socket
    sai_status_t status = sai_api_initialize(0, (service_method_table_t*)&test_services);

    ASSERT_SUCCESS("Failed to initialize api");
}

void test_enable_recording()
{
    SWSS_LOG_ENTER();

    sai_attribute_t attr;
    attr.id = SAI_REDIS_SWITCH_ATTR_RECORD;
    attr.value.booldata = true;

    sai_switch_api_t *sai_switch_api = NULL;

    sai_api_query(SAI_API_SWITCH, (void**)&sai_switch_api);

    sai_status_t status = sai_switch_api->set_switch_attribute(&attr);

    ASSERT_SUCCESS("Failed to enable recording");
}

class SaiAttrWrapper;
extern std::unordered_map<std::string,
       std::unordered_map<sai_attr_id_t,
       std::shared_ptr<SaiAttrWrapper>>> ObjectAttrHash;
extern void object_reference_insert(sai_object_id_t oid);
extern std::string get_object_meta_key_string(
        _In_ const sai_object_meta_key_t& meta_key);

sai_object_id_t create_dummy_object_id(
        _In_ sai_object_type_t objecttype)
{
    SWSS_LOG_ENTER();

    static uint64_t index = 0;

    return (((sai_object_id_t)objecttype) << 48) | ++index;
}

void test_bulk_route_set()
{
    SWSS_LOG_ENTER();

    swss::Logger::getInstance().setMinPrio(swss::Logger::SWSS_NOTICE);

    meta_init_db();

    swss::Logger::getInstance().setMinPrio(swss::Logger::SWSS_DEBUG);

    sai_status_t    status;

    sai_route_api_t *sai_route_api = NULL;

    sai_api_query(SAI_API_ROUTE, (void**)&sai_route_api);

    uint32_t count = 3;

    std::vector<sai_unicast_route_entry_t> routes;
    std::vector<sai_attribute_t> attrs;

    uint32_t index = 15;

    for (uint32_t i = index; i < index + count; ++i)
    {
        sai_unicast_route_entry_t route_entry;

        sai_object_id_t vr = create_dummy_object_id(SAI_OBJECT_TYPE_VIRTUAL_ROUTER);
        object_reference_insert(vr);
        sai_object_meta_key_t meta_key_vr = { .object_type = SAI_OBJECT_TYPE_VIRTUAL_ROUTER, .key = { .object_id = vr } };
        std::string vr_key = get_object_meta_key_string(meta_key_vr);
        ObjectAttrHash[vr_key] = { };

        sai_object_id_t hop = create_dummy_object_id(SAI_OBJECT_TYPE_NEXT_HOP);
        object_reference_insert(hop);
        sai_object_meta_key_t meta_key_hop = { .object_type = SAI_OBJECT_TYPE_NEXT_HOP, .key = { .object_id = hop } };
        std::string hop_key = get_object_meta_key_string(meta_key_hop);
        ObjectAttrHash[hop_key] = { };

        route_entry.destination.addr_family = SAI_IP_ADDR_FAMILY_IPV4;
        route_entry.destination.addr.ip4 = htonl(0x0a000000 | i);
        route_entry.destination.mask.ip4 = htonl(0xffffffff);
        route_entry.vr_id = vr;

        sai_attribute_t list[2] = { };

        sai_attribute_t &attr1 = list[0];
        sai_attribute_t &attr2 = list[1];

        attr1.id = SAI_ROUTE_ATTR_NEXT_HOP_ID;
        attr1.value.oid = hop;

        attr2.id = SAI_ROUTE_ATTR_PACKET_ACTION;
        attr2.value.s32 = SAI_PACKET_ACTION_FORWARD;

        route_entry.destination.addr_family = SAI_IP_ADDR_FAMILY_IPV4;

        status = sai_route_api->create_route(&route_entry, 2, list);

        ASSERT_SUCCESS("Failed to create route");

        routes.push_back(route_entry);

        sai_attribute_t attr;
        attr.id = SAI_ROUTE_ATTR_PACKET_ACTION;
        attr.value.s32 = SAI_PACKET_ACTION_DROP;

        status = sai_route_api->set_route_attribute(&route_entry, &attr);

        attrs.push_back(attr);

        ASSERT_SUCCESS("Failed to set route");
    }

    std::vector<sai_status_t> statuses;

    statuses.resize(attrs.size());

    for (auto &attr: attrs)
    {
        attr.value.s32 = SAI_PACKET_ACTION_FORWARD;
    }

    status = sai_bulk_set_route_entry_attribute(
        count,
        routes.data(),
        attrs.data(),
        SAI_BULK_OP_TYPE_INGORE_ERROR,
        statuses.data());

    ASSERT_SUCCESS("Failed to bulk set route");

    for (auto s: statuses)
    {
        status = s;

        ASSERT_SUCCESS("Failed to bulk set route on one of the routes");
    }

    // TODO we need to add consumer producer test here to see
    // if after consume we get pop we get expectd parameters
}

int main()
{
    swss::Logger::getInstance().setMinPrio(swss::Logger::SWSS_DEBUG);

    SWSS_LOG_ENTER();

    swss::Logger::getInstance().setMinPrio(swss::Logger::SWSS_INFO);

    return 0; // temporary disabled since docker can't connect to redis

    try
    {
        test_sai_initialize();

        test_enable_recording();

        test_bulk_route_set();

        printf("\n[ %s ]\n\n", sai_serialize_status(SAI_STATUS_SUCCESS).c_str());
    }
    catch (const std::exception &e)
    {
        SWSS_LOG_ERROR("exception: %s", e.what());

        printf("\n[ %s ]\n\n%s\n\n", sai_serialize_status(SAI_STATUS_FAILURE).c_str(), e.what());

        exit(EXIT_FAILURE);
    }

    return 0;
}
