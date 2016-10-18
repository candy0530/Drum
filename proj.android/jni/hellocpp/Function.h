/*
 * Function.h
 *
 *  Created on: 2015/3/18
 *      Author: Wei Shang Chieh
 */

#ifndef FUNCTION_H_
#define FUNCTION_H_

extern "C"  {

void showDialog(const char *title, const char *msg);
void openBT();
void sent_data(const char *data);
bool get_bluetooth_status();
jstring receive_data();
}


#endif /* FUNCTION_H_ */
