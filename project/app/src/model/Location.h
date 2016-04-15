/*
 * Location.h
 *
 *  Created on: Apr 1, 2016
 *      Author: matias
 */

#ifndef SRC_LOCATION_H_
#define SRC_LOCATION_H_


/**
 * @class Location
 * Represents the location of the user.
 *
 * @author MLuraschi
 *
 */
class Location {
public:

	/**
	* Constructor that sets the Location with initial values 0;
    */
	Location();

	/**
	 * Constructor that sets the Location.
	 *
	 * @param lat the latitude of the location to create;
	 * @param lon the longitude of the location to create;
	 *
	 */
	Location(double lat, double lon);
	virtual ~Location();

	/**
	 * Returns de latitud of the location
	 */
	double getLatitude();

	/**
	 * Returns de longitud of the location.
	 */
	double getLongitude();

	/**
	 * Changes the latitude of the location
	 *
	 * @param latitude that will become the new value
	 */
	void setLatitude(double latitude);

	/**
	 * Changes the logitude of the location
	 *
	 * @param longitude that will become the new value
	 */
	void setLongitude(double longitude);

private:
	double latitude;
	double longitude;

};

#endif /* SRC_LOCATION_H_ */
