#include "Exception.h"

namespace ofxDigitalEmulsion {
	namespace Utils {
		//---------
		Exception::Exception(const std::string message) : message(message) {	}

		//---------
		const char * Exception::what() const {
			return this->message.c_str();
		}
	}
}