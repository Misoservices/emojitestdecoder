//
//  main.c
//  emojitestdecoder
//
//  Created by Misoservices Inc. on 2021-02-05.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

const char* follows(const char* src, const char* pat) {
    const char* result = strstr(src, pat);
    if (!result) {
        return NULL;
    }
    return result + strlen(pat);
}

int main(int argc, const char * argv[]) {
    while (--argc) {
        const char* const sourcefile = argv[argc];
        char destfileStrings[2048];
        char destfileSwiftGroup[2048];
        char destfileSwiftSubgroup[2048];
        char destfileSwiftOrder[2048];
        char destfileSwiftEnum[2048];
        char destfileSwiftEnumGroup[2048];
        char destfileSwiftEnumSubgroup[2048];
        char destfileSwiftToAnnotation[2048];
        strcpy(destfileStrings, sourcefile);
        strcpy(destfileSwiftGroup, sourcefile);
        strcpy(destfileSwiftSubgroup, sourcefile);
        strcpy(destfileSwiftOrder, sourcefile);
        strcpy(destfileSwiftEnum, sourcefile);
        strcpy(destfileSwiftEnumGroup, sourcefile);
        strcpy(destfileSwiftEnumSubgroup, sourcefile);
        strcpy(destfileSwiftToAnnotation, sourcefile);
        {
            char* instance = strstr(destfileStrings, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, ".strings");
        }
        {
            char* instance = strstr(destfileSwiftGroup, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, "+group.swift");
        }
        {
            char* instance = strstr(destfileSwiftSubgroup, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, "+subgroup.swift");
        }
        {
            char* instance = strstr(destfileSwiftOrder, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, "+order.swift");
        }
        {
            char* instance = strstr(destfileSwiftEnum, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, ".swift");
        }
        {
            char* instance = strstr(destfileSwiftEnumGroup, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, "+Groups.swift");
        }
        {
            char* instance = strstr(destfileSwiftEnumSubgroup, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, "+Subgroups.swift");
        }
        {
            char* instance = strstr(destfileSwiftToAnnotation, ".txt");
            if (instance == NULL)
            {
                printf("Not a TXT file: %s\n", sourcefile);
                continue;
            }
            strcpy(instance, "+toAnnotation.swift");
        }
        printf("Processing %s: ", sourcefile);

        FILE* fs = fopen(sourcefile, "rb");
        FILE* fd = fopen(destfileStrings, "w");
        FILE* fdG = fopen(destfileSwiftGroup, "w");
        FILE* fdSg = fopen(destfileSwiftSubgroup, "w");
        FILE* fdO = fopen(destfileSwiftOrder, "w");
        FILE* fdE = fopen(destfileSwiftEnum, "w");
        FILE* fdEG = fopen(destfileSwiftEnumGroup, "w");
        FILE* fdESg = fopen(destfileSwiftEnumSubgroup, "w");
        FILE* fdTo = fopen(destfileSwiftToAnnotation, "w");
        if (!fs || !fd || !fdG || !fdSg || !fdO || !fdE || !fdEG || !fdESg || !fdTo) {
            printf("Error opening files");
            return -1;
        }
        fprintf(fdG, "public extension Emoji {\n\tvar group: Groups {\n\t\tswitch self {\n");
        fprintf(fdSg, "public extension Emoji {\n\tvar subgroup: Subgroups {\n\t\tswitch self {");
        fprintf(fdO, "public extension Emoji {\n\tvar order: Int {\n\t\tswitch self {");
        fprintf(fdTo, "public extension Emoji {\n\tvar toAnnotation: Emoji {\n\t\tswitch self {\n");
        fprintf(fdE, "public enum Emoji: String {");
        fprintf(fdEG, "public extension Emoji {\n\tenum Groups: String, CaseIterable {\n");
        fprintf(fdESg, "public extension Emoji {\n\tenum Subgroups: String, CaseIterable {");

        char line[4096];
        int processed = 0;
        char groupName[4096]; groupName[0] = 0;
        char subgroupName[4096]; subgroupName[0] = 0;
        char lastQualification[4096]; lastQualification[0] = 0;

        while (fgets(line, sizeof(line), fs)) {
            const char* groupNameLine = follows(line, "# group: ");
            if (groupNameLine) {
                strstr(groupNameLine, "\n")[0] = 0;
                strcpy(groupName, groupNameLine);
                for(int i = 0; groupName[i] != 0; ++i) {
                    if ((groupName[i] >= 'A' && groupName[i] <= 'Z') ||
                        (groupName[i] >= 'a' && groupName[i] <= 'z') ||
                        (groupName[i] >= '0' && groupName[i] <= '0')) {
                        continue;
                    }
                    groupName[i] = '_';
                }
                subgroupName[0] = 0;

                fprintf(fd, "\"group.%s\" = \"%s\";\n", groupNameLine, groupNameLine);
                fprintf(fdE, "\n\t// group: %s\n", groupNameLine);
                fprintf(fdEG, "\t\tcase %s = \"%s\"\n", groupName, groupNameLine);
                fprintf(fdESg, "\n\t\t// group: %s\n", groupNameLine);

                fprintf(fdO, "\n\t\t\t// group: %s\n", groupNameLine);
                //fprintf(fdG, "\n\t\t\t// group: %s\n", groupNameLine);
                fprintf(fdSg, "\n\t\t\t// group: %s\n", groupNameLine);
                continue;
            }

            const char* subgroupNameLine = follows(line, "# subgroup: ");
            if (subgroupNameLine) {
                strstr(subgroupNameLine, "\n")[0] = 0;
                strcpy(subgroupName, subgroupNameLine);
                for(int i = 0; subgroupName[i] != 0; ++i) {
                    if ((subgroupName[i] >= 'A' && subgroupName[i] <= 'Z') ||
                        (subgroupName[i] >= 'a' && subgroupName[i] <= 'z') ||
                        (subgroupName[i] >= '0' && subgroupName[i] <= '0')) {
                        continue;
                    }
                    subgroupName[i] = '_';
                }

                //fprintf(fd, "\"subgroup.%s\" = \"%s\";\n", subgroupNameLine, subgroupNameLine);
                fprintf(fdE, "\n\t// subgroup: %s\n", subgroupNameLine);
                fprintf(fdESg, "\t\tcase %s = \"%s\"\n", subgroupName, subgroupNameLine);

                fprintf(fdO, "\t\t\t// subgroup: %s\n", subgroupNameLine);
                //fprintf(fdG, "\t\t\t// subgroup: %s\n", subgroupNameLine);
                //fprintf(fdSg, "\t\t\t// subgroup: %s\n", subgroupNameLine);
                continue;
            }

            char text[4096];
            char name[4096];
            char comment[4096];
            if ((line[0] >= 'A' && line[0] <= 'F') ||
                (line[0] >= '0' && line[0] <= '9')) {

                name[0] = 'u';
                strcpy(text, line);
                char* textEnd = strstr(text, "  ");
                char* textEnd2 = strstr(text, " ;");
                if (!textEnd) textEnd = textEnd2;
                if (!textEnd) continue;
                if (textEnd2 && textEnd2 < textEnd) textEnd = textEnd2;
                textEnd[0] = 0;
                strcpy(name+1, text);

                for(int i = 0; name[i] != 0; ++i) {
                    if (name[i] >= 'A' && name[i] <= 'F') {
                        name[i] += ('a' - 'A');
                    }
                    else if (name[i] == ' ') {
                        name[i] = '_';
                    }
                }

                const char* commentLine = follows(line, "# ");
                if (!commentLine) {
                    comment[0] = 0;
                } else {
                    strcpy(comment, commentLine);
                    strstr(comment, "\n")[0] = 0;
                }

                fprintf(fdE, "\tcase %s = \"%s\"\t// %s\n", name, text, comment);

                fprintf(fdO, "\t\t\tcase .%s: return %d\n", name, processed);
                fprintf(fdG, "\t\t\tcase .%s: return .%s\n", name, groupName);
                fprintf(fdSg, "\t\t\tcase .%s: return .%s\n", name, subgroupName);

                if (strstr(line, "fully-qualified") != 0) {
                    if (lastQualification[0] != 0) {
                        fprintf(fdTo, ": return .%s\n", lastQualification);
                    }
                    fprintf(fdTo, "\t\t\tcase .%s", name);
                }
                else {
                    fprintf(fdTo, ", .%s", name);
                }
                strcpy(lastQualification, name);

                ++processed;
            }
        }
        fprintf(fdG, "\t\t\tdefault: fatalError()\n\t\t}\n\t}\n}\n");
        fprintf(fdSg, "\t\t\tdefault: fatalError()\n\t\t}\n\t}\n}\n");
        fprintf(fdO, "\t\t\tdefault: fatalError()\n\t\t}\n\t}\n}\n");
        fprintf(fdE, "}\n");
        fprintf(fdEG, "\t}\n}\n");
        fprintf(fdESg, "\t}\n}\n");

        fprintf(fdTo, ": return .%s\n", lastQualification);
        fprintf(fdTo, "\t\t\tdefault: fatalError()\n\t\t}\n\t}\n}\n");

        printf("%d processed.\n", processed);
        fclose(fs);
        fclose(fd);
        fclose(fdG);
        fclose(fdSg);
        fclose(fdO);
        fclose(fdE);
        fclose(fdEG);
        fclose(fdESg);
        fclose(fdTo);
    }
    return 0;
}
