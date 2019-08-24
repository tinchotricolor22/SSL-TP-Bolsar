#ifndef REPORTS_H
#define REPORTS_H

#include "../processor/processor.h"

//default_leaders_05_variation_screen returns process params preferences for default report of data_list with variation > 05
//and print screen output
ProcessParams* default_leaders_05_variation_screen();

//default_leaders_05_variation_screen returns process params preferences for default report of data_list with variation > 05
//and HTML output
ProcessParams* default_leaders_05_variation_HTML();

//default_leaders_sale_purchase_CSV returns process params preferences for default report of data_list with CSV output
ProcessParams* default_leaders_sale_purchase_CSV();

//default_preferences returns process params preferences default
ProcessParams* default_preferences();

#endif
