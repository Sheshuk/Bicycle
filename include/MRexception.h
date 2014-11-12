#include <stdexcept>
class MRexception : public std::logic_error {
public:
	MRexception(const std::string& str) noexcept: std::logic_error(str) {}
};