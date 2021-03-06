#include "sai_redis.h"
#include <cstring>

/**
 * Routine Description:
 *   @brief hostif receive function
 *
 * Arguments:
 *    @param[in] hif_id - host interface id
 *    @param[out] buffer - packet buffer
 *    @param[in,out] buffer_size - @param[in] allocated buffer size. @param[out] actual packet size in bytes
 *    @param[in,out] attr_count - @param[in] allocated list size. @param[out] number of attributes
 *    @param[out] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            SAI_STATUS_BUFFER_OVERFLOW if buffer_size is insufficient,
 *            and buffer_size will be filled with required size. Or
 *            if attr_count is insufficient, and attr_count
 *            will be filled with required count.
 *            Failure status code on error
 */
sai_status_t redis_recv_packet(
        _In_ sai_object_id_t hif_id,
        _Out_ void *buffer,
        _Inout_ sai_size_t *buffer_size,
        _Inout_ uint32_t *attr_count,
        _Out_ sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    SWSS_LOG_ERROR("not implemented");

    return SAI_STATUS_NOT_IMPLEMENTED;
}

/**
 * Routine Description:
 *   @brief hostif send function
 *
 * Arguments:
 *    @param[in] hif_id - host interface id. only valid for send through FD channel. Use SAI_NULL_OBJECT_ID for send through CB channel.
 *    @param[in] buffer - packet buffer
 *    @param[in] buffer size - packet size in bytes
 *    @param[in] attr_count - number of attributes
 *    @param[in] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_send_packet(
        _In_ sai_object_id_t hif_id,
        _In_ void *buffer,
        _In_ sai_size_t buffer_size,
        _In_ uint32_t attr_count,
        _In_ sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    SWSS_LOG_ERROR("not implemented");

    return SAI_STATUS_NOT_IMPLEMENTED;
}

/**
 * Routine Description:
 *   @brief Set user defined trap attribute value.
 *
 * Arguments:
 *    @param[in] hostif_user_defined_trap_id - host interface user defined trap id
 *    @param[in] attr - attribute
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_set_user_defined_trap_attribute(
        _In_ sai_hostif_user_defined_trap_id_t hostif_user_defined_trapid,
        _In_ const sai_attribute_t *attr)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    SWSS_LOG_ERROR("not implemented");

    return SAI_STATUS_NOT_IMPLEMENTED;
}

/**
 * Routine Description:
 *   @brief Get user defined trap attribute value.
 *
 * Arguments:
 *    @param[in] hostif_user_defined_trap_id - host interface user defined trap id
 *    @param[in] attr_count - number of attributes
 *    @param[in,out] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_get_user_defined_trap_attribute(
        _In_ sai_hostif_user_defined_trap_id_t hostif_user_defined_trapid,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    SWSS_LOG_ERROR("not implemented");

    return SAI_STATUS_NOT_IMPLEMENTED;
}

/**
 * Routine Description:
 *    @brief Create host interface trap group
 *
 * Arguments:
 *   @param[out] hostif_trap_group_id - host interface trap group id
 *   @param[in] attr_count - number of attributes
 *   @param[in] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_create_hostif_trap_group(
        _Out_ sai_object_id_t *hostif_trap_group_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_create_oid(
            SAI_OBJECT_TYPE_TRAP_GROUP,
            hostif_trap_group_id,
            attr_count,
            attr_list,
            &redis_generic_create);
}

/**
 * Routine Description:
 *    @brief Remove host interface trap group
 *
 * Arguments:
 *   @param[in] hostif_trap_group_id - host interface trap group id
 *
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_remove_hostif_trap_group(
        _In_ sai_object_id_t hostif_trap_group_id)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_remove_oid(
            SAI_OBJECT_TYPE_TRAP_GROUP,
            hostif_trap_group_id,
            &redis_generic_remove);
}

/**
 * Routine Description:
 *   @brief Set host interface trap group attribute value.
 *
 * Arguments:
 *    @param[in] hostif_trap_group_id - host interface trap group id
 *    @param[in] attr - attribute
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_set_trap_group_attribute(
        _In_ sai_object_id_t hostif_trap_group_id,
        _In_ const sai_attribute_t *attr)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_set_oid(
            SAI_OBJECT_TYPE_TRAP_GROUP,
            hostif_trap_group_id,
            attr,
            &redis_generic_set);
}

/**
 * Routine Description:
 *   @brief get host interface trap group attribute value.
 *
 * Arguments:
 *    @param[in] hostif_trap_group_id - host interface trap group id
 *    @param[in] attr_count - number of attributes
 *    @param[in,out] attr_list - array of attributes
 *
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_get_trap_group_attribute(
        _In_ sai_object_id_t hostif_trap_group_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_get_oid(
            SAI_OBJECT_TYPE_TRAP_GROUP,
            hostif_trap_group_id,
            attr_count,
            attr_list,
            &redis_generic_get);
}

/**
 * Routine Description:
 *   @brief Set trap attribute value.
 *
 * Arguments:
 *    @param[in] hostif_trap_id - host interface trap id
 *    @param[in] attr - attribute
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_set_trap_attribute(
        _In_ sai_hostif_trap_id_t hostif_trapid,
        _In_ const sai_attribute_t *attr)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_set_trap(
            hostif_trapid,
            attr,
            &redis_generic_set_trap);
}

/**
 * Routine Description:
 *   @brief Get trap attribute value.
 *
 * Arguments:
 *    @param[in] hostif_trap_id - host interface trap id
 *    @param[in] attr_count - number of attributes
 *    @param[in,out] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_get_trap_attribute(
        _In_ sai_hostif_trap_id_t hostif_trapid,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_get_trap(
            hostif_trapid,
            attr_count,
            attr_list,
            &redis_generic_get_trap);
}

/**
 * Routine Description:
 *    @brief Create host interface
 *
 * Arguments:
 *    @param[out] hif_id - host interface id
 *    @param[in] attr_count - number of attributes
 *    @param[in] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_create_hostif(
        _Out_ sai_object_id_t * hif_id,
        _In_ uint32_t attr_count,
        _In_ const sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_create_oid(
            SAI_OBJECT_TYPE_HOST_INTERFACE,
            hif_id,
            attr_count,
            attr_list,
            &redis_generic_create);
}

/**
 * Routine Description:
 *    @brief Remove host interface
 *
 * Arguments:
 *    @param[in] hif_id - host interface id
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_remove_hostif(
        _In_ sai_object_id_t hif_id)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_remove_oid(
            SAI_OBJECT_TYPE_HOST_INTERFACE,
            hif_id,
            &redis_generic_remove);
}

/**
 * Routine Description:
 *    @brief Set host interface attribute
 *
 * Arguments:
 *    @param[in] hif_id - host interface id
 *    @param[in] attr - attribute
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_set_hostif_attribute(
        _In_ sai_object_id_t hif_id,
        _In_ const sai_attribute_t *attr)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_set_oid(
            SAI_OBJECT_TYPE_HOST_INTERFACE,
            hif_id,
            attr,
            &redis_generic_set);
}

/**
 * Routine Description:
 *    @brief Get host interface attribute
 *
 * Arguments:
 *    @param[in] hif_id - host interface id
 *    @param[in] attr_count - number of attributes
 *    @param[inout] attr_list - array of attributes
 *
 * Return Values:
 *    @return SAI_STATUS_SUCCESS on success
 *            Failure status code on error
 */
sai_status_t redis_get_hostif_attribute(
        _In_ sai_object_id_t hif_id,
        _In_ uint32_t attr_count,
        _Inout_ sai_attribute_t *attr_list)
{
    std::lock_guard<std::mutex> lock(g_apimutex);

    SWSS_LOG_ENTER();

    return meta_sai_get_oid(
            SAI_OBJECT_TYPE_HOST_INTERFACE,
            hif_id,
            attr_count,
            attr_list,
            &redis_generic_get);
}

/**
 * @brief hostif methods table retrieved with sai_api_query()
 */
const sai_hostif_api_t redis_host_interface_api = {
    redis_create_hostif,
    redis_remove_hostif,
    redis_set_hostif_attribute,
    redis_get_hostif_attribute,

    redis_create_hostif_trap_group,
    redis_remove_hostif_trap_group,
    redis_set_trap_group_attribute,
    redis_get_trap_group_attribute,

    redis_set_trap_attribute,
    redis_get_trap_attribute,

    redis_set_user_defined_trap_attribute,
    redis_get_user_defined_trap_attribute,

    redis_recv_packet,
    redis_send_packet,
};
