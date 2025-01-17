/* test_settingsNVS.c: Implementation of a testable component.

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <limits.h>
#include "unity.h"
#include "settings.h"
#include "esp_log.h"


static const char *TAG = "test_settingsNVS"; // @suppress("Unused variable declaration in file scope")


/*
 *
 * you must add this into unity_config.h
 *
 * #ifdef CONFIG_UNITY_SUPPORT_64
 * #define UNITY_SUPPORT_64
 * #endif
 *
 *
 *
 */


#if !defined(UNITY_SUPPORT_64)
	#error "UNITY_SUPPORT_64 need"
#endif


TEST_CASE("init", "[init]")
{
	/* Initialize application */
	Settings_init();
}




TEST_CASE("string", "[string]")
{
	char q[] = "GeeksforGeeks";
	setString("CF-A", "string", q);
	char r[] = "Hello";
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %s %s", q, r);
    getString("CF-A", "string", "unknown", r, 33U);
    ESP_LOGI(TAG, "after: %s %s", q, r);
    TEST_ASSERT_EQUAL_STRING(q, r);
}


TEST_CASE("int8_t", "[int8_t]")
{
	int8_t q = -5;
	setS8("CF-A", "byte", q);
    int8_t r = -9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %i %i", q, r);
    r = getS8("CF-A", "byte", r);
    ESP_LOGI(TAG, "after: %i %i", q, r);
    TEST_ASSERT_EQUAL_INT8(q, r);
}

TEST_CASE("int16_t", "[int16_t]")
{
	int16_t q = -32500;
    setS16("CF-A", "word", q);
    int16_t r = -9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %i %i", q, r);
    r = getS16("CF-A", "word", r);
    ESP_LOGI(TAG, "after: %i %i", q, r);
    TEST_ASSERT_EQUAL_INT16(q, r);
}

TEST_CASE("int32_t", "[int32_t]")
{
	int32_t q = -2147000000;
    setS32("CF-A", "dword", q);
    int32_t r = -9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %i %i", q, r);
    r = getS32("CF-A", "dword", r);
    ESP_LOGI(TAG, "after: %i %i", q, r);
    TEST_ASSERT_EQUAL_INT32(q, r);
}

TEST_CASE("int64_t", "[int64_t]")
{
	int64_t q = -9223000000000000000;
	setS64("CF-A", "qword", q);
    int64_t r = -9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %lli %lli", q, r);
    r = getS64("CF-A", "qword", r);

    ESP_LOGI(TAG, "after: %lli %lli", q, r);


    const void* pq = &q;
    ESP_LOG_BUFFER_HEXDUMP(TAG, pq, 8, ESP_LOG_INFO);
    const void* pr = &r;
    ESP_LOG_BUFFER_HEXDUMP(TAG, pr, 8, ESP_LOG_INFO);


    TEST_ASSERT_EQUAL_INT64(q, r);
}

TEST_CASE("uint8_t", "[uint8_t]")
{
	uint8_t q = 5;
    setU8("CF-A", "ubyte", q);
    uint8_t r = 9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %i %i", q, r);
    r = getU8("CF-A", "ubyte", r);
    ESP_LOGI(TAG, "after: %i %i", q, r);
    TEST_ASSERT_EQUAL_UINT8(q, r);
}

TEST_CASE("uint16_t", "[uint16_t]")
{
	uint16_t q = 32500;
    setU16("CF-A", "uword", q);
    uint16_t r = 9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %i %i", q, r);
    r = getU16("CF-A", "uword", r);
    ESP_LOGI(TAG, "after: %i %i", q, r);
    TEST_ASSERT_EQUAL_UINT16(q, r);
}

TEST_CASE("uint32_t", "[uint32_t]")
{
	uint32_t q = 2147000000;
    setU32("CF-A", "udword", q);
    uint32_t r = 9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %i %i", q, r);
    r = getU32("CF-A", "udword", r);
    ESP_LOGI(TAG, "after: %i %i", q, r);
    TEST_ASSERT_EQUAL_UINT32(q, r);
}

TEST_CASE("uint64_t", "[uint64_t]")
{
	uint64_t q = 9223000000000000000;
    setU64("CF-A", "uqword", q);
    uint64_t r = 9;
    TEST_ASSERT_NOT_EQUAL(q, r);
    ESP_LOGI(TAG, "before: %lli %lli", q, r);
    r = getU64("CF-A", "uqword", r);

    ESP_LOGI(TAG, "after: %lli %lli", q, r);


    const void* pq = &q;
    ESP_LOG_BUFFER_HEXDUMP(TAG, pq, 8, ESP_LOG_INFO);
    const void* pr = &r;
    ESP_LOG_BUFFER_HEXDUMP(TAG, pr, 8, ESP_LOG_INFO);


    TEST_ASSERT_EQUAL_UINT64(q, r);
}

