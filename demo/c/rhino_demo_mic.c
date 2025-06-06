/*
    Copyright 2018-2025 Picovoice Inc.

    You may not use this file except in compliance with the license. A copy of the license is located in the "LICENSE"
    file accompanying this source.

    Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on
    an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the
    specific language governing permissions and limitations under the License.
*/

#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)

#include <windows.h>

#else

#include <dlfcn.h>

#endif

#include "pv_recorder.h"
#include "pv_rhino.h"

static volatile bool is_interrupted = false;

static void *open_dl(const char *dl_path) {

#if defined(_WIN32) || defined(_WIN64)

    return LoadLibrary(dl_path);

#else

    return dlopen(dl_path, RTLD_NOW);

#endif
}

static void *load_symbol(void *handle, const char *symbol) {

#if defined(_WIN32) || defined(_WIN64)

    return GetProcAddress((HMODULE) handle, symbol);

#else

    return dlsym(handle, symbol);

#endif
}

static void close_dl(void *handle) {

#if defined(_WIN32) || defined(_WIN64)

    FreeLibrary((HMODULE) handle);

#else

    dlclose(handle);

#endif
}

static void print_dl_error(const char *message) {

#if defined(_WIN32) || defined(_WIN64)

    fprintf(stderr, "%s with code '%lu'.\n", message, GetLastError());

#else

    fprintf(stderr, "%s with '%s'.\n", message, dlerror());

#endif
}

static struct option long_options[] = {
        {"access_key",            required_argument, NULL, 'a'},
        {"library_path",          required_argument, NULL, 'l'},
        {"model_path",            required_argument, NULL, 'm'},
        {"context_path",          required_argument, NULL, 'c'},
        {"audio_device_index",    required_argument, NULL, 'd'},
        {"sensitivity",           required_argument, NULL, 't'},
        {"endpoint_duration_sec", required_argument, NULL, 'u'},
        {"require_endpoint",      required_argument, NULL, 'e'},
        {"show_audio_devices",    no_argument,       NULL, 's'},
};

static void print_usage(const char *program_name) {
    fprintf(stderr,
            "Usage : %s -a ACCESS_KEY -l LIBRARY_PATH -m MODEL_PATH -c CONTEXT_PATH [-d AUDIO_DEVICE_INDEX] "
            "[-t SENSITIVITY]  [-u, --endpoint_duration_sec] [-e, --require_endpoint (true,false)]\n"
            "        %s [-s, --show_audio_devices]\n",
            program_name,
            program_name);
}

void interrupt_handler(int _) {
    (void) _;
    is_interrupted = true;
}

void show_audio_devices(void) {
    char **devices = NULL;
    int32_t count = 0;

    pv_recorder_status_t status = pv_recorder_get_available_devices(&count, &devices);
    if (status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to get audio devices with: %s.\n", pv_recorder_status_to_string(status));
        exit(1);
    }

    fprintf(stdout, "Printing devices...\n");
    for (int32_t i = 0; i < count; i++) {
        fprintf(stdout, "index: %d, name: %s\n", i, devices[i]);
    }

    pv_recorder_free_available_devices(count, devices);
}

void print_error_message(char **message_stack, int32_t message_stack_depth) {
    for (int32_t i = 0; i < message_stack_depth; i++) {
        fprintf(stderr, "  [%d] %s\n", i, message_stack[i]);
    }
}

int picovoice_main(int argc, char *argv[]) {
    signal(SIGINT, interrupt_handler);

    const char *access_key = NULL;
    const char *library_path = NULL;
    const char *model_path = NULL;
    const char *context_path = NULL;
    int32_t device_index = -1;
    float sensitivity = 0.5f;
    float endpoint_duration_sec = 1.f;
    bool require_endpoint = true;

    int c;
    while ((c = getopt_long(argc, argv, "a:l:m:c:d:t:u:e:s", long_options, NULL)) != -1) {
        switch (c) {
            case 'a':
                access_key = optarg;
                break;
            case 'l':
                library_path = optarg;
                break;
            case 'm':
                model_path = optarg;
                break;
            case 'c':
                context_path = optarg;
                break;
            case 'd':
                device_index = (int32_t) strtol(optarg, NULL, 10);
                break;
            case 't':
                sensitivity = strtof(optarg, NULL);
                break;
            case 'u':
                endpoint_duration_sec = strtof(optarg, NULL);
                break;
            case 'e':
                require_endpoint = (strcmp(optarg, "false") != 0);
                break;
            case 's':
                show_audio_devices();
                return 0;
            default:
                exit(1);
        }
    }

    if (!access_key || !library_path || !model_path || !context_path) {
        print_usage(argv[0]);
        exit(1);
    }

    void *rhino_library = open_dl(library_path);
    if (!rhino_library) {
        fprintf(stderr, "failed to open library.\n");
        exit(1);
    }

    const char *(*pv_status_to_string_func)(pv_status_t) = load_symbol(rhino_library, "pv_status_to_string");
    if (!pv_status_to_string_func) {
        print_dl_error("failed to load 'pv_status_to_string'");
        exit(1);
    }

    int32_t (*pv_sample_rate_func)() = load_symbol(rhino_library, "pv_sample_rate");
    if (!pv_sample_rate_func) {
        print_dl_error("failed to load 'pv_sample_rate'");
        exit(1);
    }

    pv_status_t (*pv_rhino_init_func)(
            const char *,
            const char *,
            const char *,
            float,
            float,
            bool,
            pv_rhino_t **) =
            load_symbol(rhino_library, "pv_rhino_init");
    if (!pv_rhino_init_func) {
        print_dl_error("failed to load 'pv_rhino_init'");
        exit(1);
    }

    void (*pv_rhino_delete_func)(pv_rhino_t *) = load_symbol(rhino_library, "pv_rhino_delete");
    if (!pv_rhino_delete_func) {
        print_dl_error("failed to load 'pv_rhino_delete'");
        exit(1);
    }

    pv_status_t (*pv_rhino_process_func)(pv_rhino_t *, const int16_t *, bool *) =
            load_symbol(rhino_library, "pv_rhino_process");
    if (!pv_rhino_process_func) {
        print_dl_error("failed to load 'pv_rhino_process'");
        exit(1);
    }

    pv_status_t (*pv_rhino_is_understood_func)(const pv_rhino_t *, bool *) =
            load_symbol(rhino_library, "pv_rhino_is_understood");
    if (!pv_rhino_is_understood_func) {
        print_dl_error("failed to load 'pv_rhino_is_understood'");
        exit(1);
    }

    pv_status_t (*pv_rhino_get_intent_func)(const pv_rhino_t *, const char **, int32_t *, const char ***, const char ***) =
            load_symbol(rhino_library, "pv_rhino_get_intent");
    if (!pv_rhino_get_intent_func) {
        print_dl_error("failed to load 'pv_rhino_get_intent'");
        exit(1);
    }

    pv_status_t (*pv_rhino_free_slots_and_values_func)(const pv_rhino_t *, const char **, const char **) =
            load_symbol(rhino_library, "pv_rhino_free_slots_and_values");
    if (!pv_rhino_free_slots_and_values_func) {
        print_dl_error("failed to load 'pv_rhino_free_slots_and_values'");
        exit(1);
    }

    pv_status_t (*pv_rhino_reset_func)(pv_rhino_t *) =
            load_symbol(rhino_library, "pv_rhino_reset");
    if (!pv_rhino_reset_func) {
        print_dl_error("failed to load 'pv_rhino_reset'");
        exit(1);
    }

    pv_status_t (*pv_rhino_context_info_func)(const pv_rhino_t *, const char **) =
            load_symbol(rhino_library, "pv_rhino_context_info");
    if (!pv_rhino_context_info_func) {
        print_dl_error("failed to load 'pv_rhino_context_info'");
        exit(1);
    }

    int32_t (*pv_rhino_frame_length_func)() = load_symbol(rhino_library, "pv_rhino_frame_length");
    if (!pv_rhino_frame_length_func) {
        print_dl_error("failed to load 'pv_rhino_frame_length'n");
        exit(1);
    }

    const char *(*pv_rhino_version_func)() = load_symbol(rhino_library, "pv_rhino_version");
    if (!pv_rhino_version_func) {
        print_dl_error("failed to load 'pv_rhino_version'");
        exit(1);
    }

    pv_status_t (*pv_get_error_stack_func)(char ***, int32_t *) = load_symbol(rhino_library, "pv_get_error_stack");
    if (!pv_get_error_stack_func) {
        print_dl_error("failed to load 'pv_get_error_stack_func'");
        exit(1);
    }

    void (*pv_free_error_stack_func)(char **) = load_symbol(rhino_library, "pv_free_error_stack");
    if (!pv_free_error_stack_func) {
        print_dl_error("failed to load 'pv_free_error_stack_func'");
        exit(1);
    }

    char **message_stack = NULL;
    int32_t message_stack_depth = 0;
    pv_status_t error_status = PV_STATUS_RUNTIME_ERROR;

    pv_rhino_t *rhino = NULL;
    pv_status_t status = pv_rhino_init_func(
            access_key,
            model_path,
            context_path,
            sensitivity,
            endpoint_duration_sec,
            require_endpoint,
            &rhino);
    if (status != PV_STATUS_SUCCESS) {
        fprintf(stderr, "'pv_rhino_init' failed with '%s'", pv_status_to_string_func(status));
        error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

        if (error_status != PV_STATUS_SUCCESS) {
            fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
            exit(1);
        }

        if (message_stack_depth > 0) {
            fprintf(stderr, ":\n");
            print_error_message(message_stack, message_stack_depth);
        } 

        pv_free_error_stack_func(message_stack);
        exit(1);
    }

    fprintf(stdout, "Picovoice Rhino Speech-to-Intent (%s)\n\n", pv_rhino_version_func());

    const int32_t frame_length = pv_rhino_frame_length_func();
    pv_recorder_t *recorder = NULL;
    pv_recorder_status_t recorder_status = pv_recorder_init(frame_length, device_index, 100, &recorder);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to initialize device with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    const char *context_info = NULL;
    status = pv_rhino_context_info_func(rhino, &context_info);
    if (status != PV_STATUS_SUCCESS) {
        fprintf(stderr, "'pv_rhino_context_info' failed with '%s'", pv_status_to_string_func(status));
        error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

        if (error_status != PV_STATUS_SUCCESS) {
            fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
            exit(1);
        }

        if (message_stack_depth > 0) {
            fprintf(stderr, ":\n");
            print_error_message(message_stack, message_stack_depth);
        } 

        pv_free_error_stack_func(message_stack);
        exit(1);
    }
    fprintf(stdout, "%s\n\n", context_info);

    const char *selected_device = pv_recorder_get_selected_device(recorder);
    fprintf(stdout, "Selected device: %s.\n", selected_device);
    fprintf(stdout, "Listening...\n\n");

    recorder_status = pv_recorder_start(recorder);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to start device with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    int16_t *pcm = malloc(frame_length * sizeof(int16_t));
    if (!pcm) {
        fprintf(stderr, "Failed to allocate pcm memory.\n");
        exit(1);
    }

    while (!is_interrupted) {

        recorder_status = pv_recorder_read(recorder, pcm);
        if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
            fprintf(stderr, "Failed to read with %s.\n", pv_recorder_status_to_string(recorder_status));
            exit(1);
        }

        bool is_finalized = false;
        status = pv_rhino_process_func(
                rhino,
                pcm,
                &is_finalized);

        if (status != PV_STATUS_SUCCESS) {
            fprintf(stderr, "'pv_rhino_process' failed with '%s'", pv_status_to_string_func(status));
            error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

            if (error_status != PV_STATUS_SUCCESS) {
                fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
                exit(1);
            }

            if (message_stack_depth > 0) {
                fprintf(stderr, ":\n");
                print_error_message(message_stack, message_stack_depth);
            } 

            pv_free_error_stack_func(message_stack);
            exit(1);
        }

        if (is_finalized) {
            bool is_understood = false;
            status = pv_rhino_is_understood_func(rhino, &is_understood);
            if (status != PV_STATUS_SUCCESS) {
                fprintf(stderr, "'pv_rhino_is_understood' failed with '%s'", pv_status_to_string_func(status));
                error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

                if (error_status != PV_STATUS_SUCCESS) {
                    fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
                    exit(1);
                }

                if (message_stack_depth > 0) {
                    fprintf(stderr, ":\n");
                    print_error_message(message_stack, message_stack_depth);
                } 

                pv_free_error_stack_func(message_stack);
                exit(1);
            }

            const char *intent = NULL;
            int32_t num_slots = 0;
            const char **slots = NULL;
            const char **values = NULL;

            if (is_understood) {
                status = pv_rhino_get_intent_func(
                        rhino,
                        &intent,
                        &num_slots,
                        &slots,
                        &values);
                if (status != PV_STATUS_SUCCESS) {
                    fprintf(stderr, "'pv_rhino_get_intent' failed with '%s'", pv_status_to_string_func(status));
                    error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

                    if (error_status != PV_STATUS_SUCCESS) {
                        fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
                        exit(1);
                    }

                    if (message_stack_depth > 0) {
                        fprintf(stderr, ":\n");
                        print_error_message(message_stack, message_stack_depth);
                    } 

                    pv_free_error_stack_func(message_stack);
                    exit(1);
                }
            }

            fprintf(stdout, "{\n");
            fprintf(stdout, "    'is_understood' : '%s',\n", is_understood ? "true" : "false");
            if (is_understood) {
                fprintf(stdout, "    'intent' : '%s',\n", intent);
                if (num_slots > 0) {
                    fprintf(stdout, "    'slots' : {\n");
                    for (int32_t i = 0; i < num_slots; i++) {
                        fprintf(stdout, "        '%s' : '%s',\n", slots[i], values[i]);
                    }
                    fprintf(stdout, "    }\n");
                }
            }
            fprintf(stdout, "}\n");
            fflush(stdout);

            if (is_understood) {
                status = pv_rhino_free_slots_and_values_func(rhino, slots, values);
                if (status != PV_STATUS_SUCCESS) {
                    fprintf(stderr, "'pv_rhino_free_slots_and_values' failed with '%s'", pv_status_to_string_func(status));
                    error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

                    if (error_status != PV_STATUS_SUCCESS) {
                        fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
                        exit(1);
                    }

                    if (message_stack_depth > 0) {
                        fprintf(stderr, ":\n");
                        print_error_message(message_stack, message_stack_depth);
                    } 

                    pv_free_error_stack_func(message_stack);
                    exit(1);
                }
            }

            status = pv_rhino_reset_func(rhino);
            if (status != PV_STATUS_SUCCESS) {
                fprintf(stderr, "'pv_rhino_reset' failed with '%s'", pv_status_to_string_func(status));
                error_status = pv_get_error_stack_func(&message_stack, &message_stack_depth);

                if (error_status != PV_STATUS_SUCCESS) {
                    fprintf(stderr, ".\nUnable to get Rhino error state with '%s'\n", pv_status_to_string_func(error_status));
                    exit(1);
                }

                if (message_stack_depth > 0) {
                    fprintf(stderr, ":\n");
                    print_error_message(message_stack, message_stack_depth);
                } 

                pv_free_error_stack_func(message_stack);
                exit(1);
            }
        }
    }
    fprintf(stdout, "\n");

    recorder_status = pv_recorder_stop(recorder);
    if (recorder_status != PV_RECORDER_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to stop device with %s.\n", pv_recorder_status_to_string(recorder_status));
        exit(1);
    }

    free(pcm);
    pv_recorder_delete(recorder);
    pv_rhino_delete_func(rhino);
    close_dl(rhino_library);

    return 0;
}

int main(int argc, char *argv[]) {

#if defined(_WIN32) || defined(_WIN64)

#define UTF8_COMPOSITION_FLAG (0)
#define NULL_TERMINATED       (-1)

    LPWSTR *wargv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (wargv == NULL) {
        fprintf(stderr, "CommandLineToArgvW failed\n");
        exit(1);
    }

    char *utf8_argv[argc];

    for (int i = 0; i < argc; ++i) {
        // WideCharToMultiByte: https://docs.microsoft.com/en-us/windows/win32/api/stringapiset/nf-stringapiset-widechartomultibyte
        int arg_chars_num = WideCharToMultiByte(CP_UTF8, UTF8_COMPOSITION_FLAG, wargv[i], NULL_TERMINATED, NULL, 0, NULL, NULL);
        utf8_argv[i] = (char *) malloc(arg_chars_num * sizeof(char));
        if (!utf8_argv[i]) {
            fprintf(stderr, "failed to to allocate memory for converting args");
        }
        WideCharToMultiByte(CP_UTF8, UTF8_COMPOSITION_FLAG, wargv[i], NULL_TERMINATED, utf8_argv[i], arg_chars_num, NULL, NULL);
    }

    LocalFree(wargv);
    argv = utf8_argv;

#endif

    int result = picovoice_main(argc, argv);

#if defined(_WIN32) || defined(_WIN64)

    for (int i = 0; i < argc; ++i) {
        free(utf8_argv[i]);
    }

#endif

    return result;
}
