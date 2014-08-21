/* yamldumper.cc
 * vim: set tw=80:
 * Eryn Wells <eryn@erynwells.me>
 */
/**
 * A small utility that reads a YAML file and dumps the parser events.
 */

#include <cstdio>
#include <iostream>

#include "yaml.h"


int
main(int argc,
     char* argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [yaml_file ...]\n", argv[0]);
        return -1;
    }

    bool writeNewline = false;
    for (int i = 1; i < argc; i++) {
        if (writeNewline) {
            printf("\n");
        }

        printf("--- %s\n", argv[i]);

        yaml_parser_t parser;
        yaml_parser_initialize(&parser);

        FILE *f = fopen(argv[i], "rb");
        if (!f) {
            fprintf(stderr, "Couldn't open file.\n");
        }
        yaml_parser_set_input_file(&parser, f);

        bool done = false;
        yaml_event_t event;
        while (!done) {
            if (!yaml_parser_parse(&parser, &event)) {
                fprintf(stderr, "Error parsing file.\n");
                goto error;
            }

            switch (event.type) {
                case YAML_NO_EVENT:
                    std::cout << "YAML_NO_EVENT\n";
                    break;

                case YAML_STREAM_START_EVENT:
                    std::cout << "YAML_STREAM_START_EVENT\n";
                    break;
                case YAML_STREAM_END_EVENT:
                    std::cout << "YAML_STREAM_END_EVENT\n";
                    break;

                case YAML_DOCUMENT_START_EVENT:
                    std::cout << "YAML_DOCUMENT_START_EVENT\n";
                    break;
                case YAML_DOCUMENT_END_EVENT:
                    std::cout << "YAML_DOCUMENT_END_EVENT\n";
                    break;

                case YAML_ALIAS_EVENT:
                    std::cout << "YAML_ALIAS_EVENT\n";
                    break;
                case YAML_SCALAR_EVENT:
                    printf("YAML_SCALAR_EVENT value='%s'\n",
                           std::string((const char *)event.data.scalar.value,
                                       event.data.scalar.length).c_str());
                    break;

                case YAML_SEQUENCE_START_EVENT:
                    std::cout << "YAML_SEQUENCE_START_EVENT\n";
                    break;
                case YAML_SEQUENCE_END_EVENT:
                    std::cout << "YAML_SEQUENCE_END_EVENT\n";
                    break;

                case YAML_MAPPING_START_EVENT:
                    std::cout << "YAML_MAPPING_START_EVENT\n";
                    break;
                case YAML_MAPPING_END_EVENT:
                    std::cout << "YAML_MAPPING_END_EVENT\n";
                    break;
            }

            done = (event.type == YAML_STREAM_END_EVENT);
            yaml_event_delete(&event);
        } /* while (!done) */

error:
        yaml_parser_delete(&parser);
        fclose(f);
        writeNewline = true;
    } /* for file : argv */

    return 0;
}
