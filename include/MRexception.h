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
	MR_out_of_range(size_t idx, size_t low, size_t upp) noexcept:MRexception(make_message(idx,low,upp)){};
private:
	std::string make_message(size_t idx, size_t low, size_t upp){
		char msg[200];
		sprintf(msg,"index %ld out of range [%ld..%ld]",idx,low,upp);
		return msg;
	}
};


#endif