#ifndef MR_EXCEPTION__H
#define MR_EXCEPTION__H value
#include <string>
#include <stdexcept>

class MRexception : public std::logic_error {
public:
	MRexception(const std::string& str) noexcept: std::logic_error(str) {}
};

class MR_out_of_range: public MRexception
{
public:
	MR_out_of_range(size_t idx, size_t size) noexcept:
	MRexception("Index ["+std::to_string(idx)+"] out of range [0.."+std::to_string(size)+"]"){	};
};

#endif