#include <check.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Simulates the vulnerable pattern from RFX_AE_Utils.h
// In production, this would be imported directly, but the header uses C++ (std::string)
// so we test the security invariant on the concatenation pattern

static bool contains_dangerous_gmic_commands(const char *script) {
    // G'MIC commands that can execute system commands or access filesystem
    const char *dangerous_patterns[] = {
        "exec", "system", "sh ", "bash", "cmd ",
        "x \"", "x '",  // G'MIC exec shorthand
        "output", "o ",  // file write operations
        "input", "i ",   // could be used for path traversal
        NULL
    };
    
    for (int i = 0; dangerous_patterns[i] != NULL; i++) {
        if (strstr(script, dangerous_patterns[i]) != NULL) {
            return true;
        }
    }
    return false;
}

START_TEST(test_gmic_script_injection_blocked)
{
    // Invariant: Scripts concatenated into command strings must not contain
    // system execution commands that could escape the G'MIC sandbox
    const char *payloads[] = {
        "x \"rm -rf /\"",                    // Direct system command injection
        "-exec bash -c 'cat /etc/passwd'",   // Shell execution attempt
        "blur 3",                            // Valid benign G'MIC command
        "output /tmp/exfil.txt",             // File write attempt
    };
    int num_payloads = sizeof(payloads) / sizeof(payloads[0]);

    for (int i = 0; i < num_payloads; i++) {
        bool is_dangerous = contains_dangerous_gmic_commands(payloads[i]);
        
        // Benign command (index 2) should pass, others should be flagged
        if (i == 2) {
            ck_assert_msg(!is_dangerous, 
                "Valid G'MIC command incorrectly flagged: %s", payloads[i]);
        } else {
            ck_assert_msg(is_dangerous,
                "Dangerous payload not detected: %s", payloads[i]);
        }
    }
}
END_TEST

Suite *security_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Security");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_gmic_script_injection_blocked);
    suite_add_tcase(s, tc_core);

    return s;
}

int main(void)
{
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = security_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}