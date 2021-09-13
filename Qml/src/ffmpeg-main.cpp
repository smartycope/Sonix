#include "ffmpeg.hpp"
#include "ffmpeg/libavdevice/avdevice.h"

// [added]
// #include "src/cope.hpp"
#include <algorithm>


// int main(int argc, char **argv)
// [added] changed main to ffmpeg and changed the parameters
// int ffmpeg(int argc, char **argv)
// int ffmpeg(std::vector<char*> args)
int ffmpeg(std::vector<std::string> args)
{
    std::vector<char*> result;
    // Remember the nullptr terminator
    result.reserve(args.size()+1);

    std::transform(begin(args), end(args),
                std::back_inserter(result),
                [](std::string &s) { return s.data(); }
                );
    result.push_back(nullptr);

    int argc = result.size() - 1;
    char** argv = result.data();

    // debugArgv(argc, argv);

    int i, ret;
    BenchmarkTimeStamps ti;

    init_dynload();

    register_exit(ffmpeg_cleanup);

    setvbuf(stderr,NULL,_IONBF,0); /* win32 runtime needs this */

    av_log_set_flags(AV_LOG_SKIP_REPEATED);
    parse_loglevel(argc, argv, options);

    if(argc>1 && !strcmp(argv[1], "-d")){
        run_as_daemon=1;
        // [added]
        av_log_set_callback(log_callback_null);
        // av_log_set_callback(log_callback_help);
        argc--;
        argv++;
    }

// This is manually set to 0 in config.h anyway
#if CONFIG_AVDEVICE
    // avdevice_register_all();
#endif
    avformat_network_init();

    show_banner(argc, argv, options);

    /* parse options and open all input/output files */
    ret = ffmpeg_parse_options(argc, argv);
    if (ret < 0)
        exit_program(1);

    if (nb_output_files <= 0 && nb_input_files == 0) {
        show_usage();
        av_log(NULL, AV_LOG_WARNING, "Use -h to get full help or, even better, run 'man %s'\n", program_name);
        exit_program(1);
    }

    /* file converter / grab */
    if (nb_output_files <= 0) {
        av_log(NULL, AV_LOG_FATAL, "At least one output file must be specified\n");
        exit_program(1);
    }

    for (i = 0; i < nb_output_files; i++) {
        if (strcmp(output_files[i]->ctx->oformat->name, "rtp"))
            want_sdp = 0;
    }

    current_time = ti = get_benchmark_time_stamps();
    if (transcode() < 0)
        exit_program(1);
    if (do_benchmark) {
        int64_t utime, stime, rtime;
        current_time = get_benchmark_time_stamps();
        utime = current_time.user_usec - ti.user_usec;
        stime = current_time.sys_usec  - ti.sys_usec;
        rtime = current_time.real_usec - ti.real_usec;
        av_log(NULL, AV_LOG_INFO,
               "bench: utime=%0.3fs stime=%0.3fs rtime=%0.3fs\n",
               utime / 1000000.0, stime / 1000000.0, rtime / 1000000.0);
    }
    av_log(NULL, AV_LOG_DEBUG, "%" PRIu64" frames successfully decoded, %" PRIu64" decoding errors\n",
           decode_error_stat[0], decode_error_stat[1]);
    if ((decode_error_stat[0] + decode_error_stat[1]) * max_error_rate < decode_error_stat[1])
        exit_program(69);

    exit_program(received_nb_signals ? 255 : main_return_code);
    return main_return_code;
}
