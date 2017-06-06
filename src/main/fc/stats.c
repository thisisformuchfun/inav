
#include "platform.h"

#ifdef STATS

#include "fc/stats.h"

#include "drivers/time.h"
#include "navigation/navigation.h"

#include "fc/config.h"
#include "config/parameter_group.h"
#include "config/parameter_group_ids.h"

PG_REGISTER_WITH_RESET_FN(statsConfig_t, statsConfig, PG_STATS_CONFIG, 0);

void pgResetFn_statsConfig(statsConfig_t *instance)
{
    instance->stats_enabled = 0;
    instance->stats_total_time = 0;
    instance->stats_total_dist = 0;
}

static uint32_t arm_millis;
static uint32_t arm_distance_cm;

void statsOnArm(void)
{
    arm_millis      = millis();
    arm_distance_cm = getTotalTravelDistance();
}

void statsOnDisarm(void)
{
    if (statsConfig()->stats_enabled) {
        statsConfigMutable()->stats_total_time += (millis() - arm_millis) / 1000;	//[s]
        statsConfigMutable()->stats_total_dist += (getTotalTravelDistance() - arm_distance_cm) / 100;	//[m]
        writeEEPROM();
    }
}

#endif
