#include <string>
#include <unistd.h>

void	write_fd(int fd, std::string str)
{
	write(fd, str.c_str(), str.size());
}