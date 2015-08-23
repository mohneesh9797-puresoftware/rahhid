#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <hidapi/hidapi.h>

int main(int argc, char *argv[])
{
    int res;
    hid_device *handle;
    unsigned char command[2] = {0};
    unsigned char report[9] = {0};

    res = hid_init();
    if (res < 0)
        return -1;

    handle = hid_open(0x4d8, 0xf6fe, NULL);
    if (handle == NULL)
        return -1;

    command[0] = '\x10';
    res = hid_send_feature_report(handle, command, 2);
    if (res < 0)
        return -1;
    printf("Switched LCD backlight off\n");

    command[0] = '\x40';
    res = hid_send_feature_report(handle, command, 2);
    if (res < 0)
        return -1;
    printf("Switched buzzer off\n");

    res = hid_get_feature_report(handle, report, 9);
    if (res < 0)
        return -1;

    unsigned int clock = report[1] + report[2] * 256 + report[3] * 256 * 256;
    unsigned int counts = report[5] + report[6] * 256 + report[7] * 256 * 256;
    printf("Clock: %i, counts: %i\n", clock, counts);

    double cpm = counts * 1000.0 * 60 / clock;
    printf("%g CPM\n", cpm);

    double uSvph = cpm / 171.2;
    printf("%g microSv/h\n", uSvph);

    double ccpm = cpm / (1 - (cpm * (200e-6/60)));
    printf("%g corrected CPM\n", ccpm);

    double cuSvph = ccpm / 171.2;
    double std = (sqrt(counts) * 1000.0 * 60 / clock) / 171.2;
    printf("%g+-%g microSv/h\n", cuSvph, std);

    if (argc == 2) {
        char *thingspeak_command = NULL;
        res = asprintf(&thingspeak_command,
                "curl -k --data 'api_key=%s&field1=%f&field2=%f&field3=%f&field4=%f&field5=%f' https://api.thingspeak.com/update > /dev/null",
                argv[1], cpm, uSvph, ccpm, cuSvph, std);
        if (res < 0)
            return -1;
        res = system(thingspeak_command);
        if (res < 0) {
            printf("Cannot upload data to ThingSpeak\n");
            return -1;
        }
        else if (WEXITSTATUS(res) != 0) {
            printf("cURL failed to upload data to ThingSpeak\n");
            return -1;
        }
        free(thingspeak_command);
        thingspeak_command = NULL;
    }

    res = hid_exit();
    if (res < 0)
        return -1;

    return 0;
}
