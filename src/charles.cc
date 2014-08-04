/* charles.c
 *
 * Entry point for Charles, including main().
 *
 * Eryn Wells <eryn@erynwells.me>
 */

#include <cstdio>
#include <unistd.h>

#include "basics.h"
#include "log.hh"
#include "light.h"
#include "reader_yaml.hh"
#include "scene.h"
#include "writer_png.h"

#define LOG_NAME "ROOT"
#include "logModule.hh"


int verbosity = 0;


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

    scene.get_ambient().set_intensity(1.0);

#if 0
    Material *m1 = new Material();
    m1->set_diffuse_color(Color::Red);
    Material *m2 = new Material();
    m2->set_diffuse_color(Color::Green);
    Material *m3 = new Material();
    m3->set_diffuse_color(Color::Blue);

    // Make some spheres.
    Sphere *s1 = new Sphere(Vector3(0, 0.5, 2), 0.33);
    Sphere *s2 = new Sphere(Vector3(-0.33, 0, 2), 0.33);
    Sphere *s3 = new Sphere(Vector3(0.33, 0, 2), 0.33);
    s1->set_material(m1);
    s2->set_material(m2);
    s3->set_material(m3);
    scene.add_shape(s1);
    scene.add_shape(s2);
    scene.add_shape(s3);

    // Make a plane
    /*
    Plane *p1 = new Plane(Vector3(0, 460, 400), Vector3(0, 1, 0.01));
    p1->set_material(m1);
    scene.add_shape(p1);
    */
#endif

    PointLight *l1 = new PointLight(Vector3(4.0, 6.0, 1.0), Color::White, 0.8);
    scene.add_light(l1);

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
    scene.render();

    /* Write rendered scene to PNG file. */
    PNGWriter writer;
    scene.write(writer, outfile);

    if (logLevel > 0) {
        Log::Close();
    }

    return 0;
}
