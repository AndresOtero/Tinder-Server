//
// Created by matias on 4/30/16.
//

#ifndef TINDER_SERVER_INTEREST_H
#define TINDER_SERVER_INTEREST_H

#include <string>

using namespace std;

/**
 * @class Interest
 * Represents a user interest of the model
 *
 * @author MLuraschi
 */
class Interest {
public:
	/**
	 * Default constructor
	 *
	 * @param category category of the interest.
	 * @param value value of the interest in the given category.
	 */
	Interest(string category, string value);
	virtual ~Interest();

	/**
	 * Override of the == operator
	 *
	 * @param other Interest to compare this with. Returns true if both are the same category and value.
	 */
	bool operator== (const Interest& other);

	/**
	 * Returns the category of the Interests.
	 */
	const string &getCategory() const {
		return category;
	}

	/**
	 * Returns the value of the interest.
	 */
	const string &getValue() const {
		return value;
	}

private:
	string category;
	string value;
};


#endif //TINDER_SERVER_INTEREST_H
