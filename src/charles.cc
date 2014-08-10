/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstdio>
#include <unistd.h>

#include "log.hh"
#include "light.hh"
#include "reader_yaml.hh"
#include "scene.hh"
#include "writer_png.h"
#include "basics/basics.hh"

#define LOG_NAME "ROOT"
#include "logModule.hh"


using namespace charles;
using namespace charles::basics;


static void
usage(const char *progname)
{
    fprintf(stderr, "Usage: %s [-hv] [-l <logfile>] [-L <log level>] [-o <outfile>] <infile ...>\n",
            progname);
}


int
main(int argc,
     const char *argv[])
{
    using namespace charles::log;

    Scene scene;

    PointLight *l1 = new PointLight(Vector4(4.0, 6.0, 1.0), Color::White, 0.8);
    scene.AddLight(l1);

    std::string logFilename;
    unsigned int logLevel = 0;

    std::string outfile, infile;

    int opt;
    while ((opt = getopt(argc, (char *const *)argv, "hl:L:o:v:")) != -1) {
        switch (opt) {
            case 'h':
                usage(argv[0]);
                exit(0);
                break;
            case 'l':
                logFilename = optarg;
                break;
            case 'L':
                logLevel = std::stoul(optarg);
                break;
            case 'o':
                outfile = optarg;
                break;
            case 'v':
                break;
        }
    }

    /* Set up logging */
    if (logLevel > 0) {
        if (logFilename.empty()) {
            logFilename = "charles.log";
        }
        Log::Init(logFilename, logLevel);
    }

    if (optind >= argc) {
        LOG_ERROR << "Input file required.";
        fprintf(stderr, "Input file required.\n");
        usage(argv[0]);
        return -1;
    }

    infile = argv[optind];

    if (outfile.empty()) {
        outfile = "charles_out.png";
    }

    /* Parse YAML files. */
    YAMLReader reader(scene);
    for (int i = optind; i < argc; i++) {
        reader.read_file(infile);
    }

    /* Call tracer. */
    LOG_INFO << "Beginning render";
    scene.Render();

    /* Write rendered scene to PNG file. */
    PNGWriter writer;
    scene.Write(writer, outfile);

    if (logLevel > 0) {
        Log::Close();
    }

    return 0;
}
