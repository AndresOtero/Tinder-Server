/*
 * Location.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_LOCATION_H_
#define SRC_LOCATION_H_


class Location {
public:
	Location();
	Location(double lat, double lon);
	virtual ~Location();
	double getLatitude();
	double getLongitude();

private:
	double latitude;
	double longitude;

};

#endif /* SRC_LOCATION_H_ */
