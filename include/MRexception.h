#ifndef MR_EXCEPTION__H
#define MR_EXCEPTION__H value
#include <string>
#include <stdexcept>

class MRexception : public std::logic_error {
public:
	MRexception(const std::string& str) noexcept: std::logic_error(str) {}
};

class MR_ValOutOfRange: public MRexception
{
public:
	MR_ValOutOfRange(double val, double low, double upp) noexcept:MRexception(make_message(val,low,upp)){};
private:
	std::string make_message(double val, double low, double upp){
		char msg[200];
		sprintf(msg,"value %f out of range [%f..%f]",val,low,upp);
		return msg;
	}
};

class MR_IdxOutOfRange: public MRexception
{
public:
	MR_IdxOutOfRange(size_t idx, size_t low, size_t upp) noexcept:MRexception(make_message(idx,low,upp)){};
private:
	std::string make_message(size_t idx, size_t low, size_t upp){
		char msg[200];
		sprintf(msg,"index %ld out of range [%ld..%ld]",idx,low,upp);
		return msg;
	}
};

class MR_length_mismatch: public MRexception
{
public:
	MR_length_mismatch(size_t len1, size_t len2) noexcept:MRexception(make_message(len1,len2)){};
private:
	std::string make_message(size_t len1, size_t len2){
		char msg[200];
		sprintf(msg,"array length mismatch: %ld!=%ld",len1,len2);
		return msg;
	}
};

#endif