
#include <iostream>
#include <stdio.h>

#include <sys/wait.h>
#include <sys/types.h>


int main() 
{
  int status = 9;
  std::cout << SIGKILL << std::endl;
  std::cout << WIFEXITED(status) << std::endl;
  std::cout << WEXITSTATUS(status) << std::endl;
  std::cout << WIFSIGNALED(status) << std::endl;;
  std::cout << WTERMSIG(status) << std::endl;;
  std::cout << WCOREDUMP(status) << std::endl;;
  std::cout << WIFSTOPPED(status) << std::endl;;
  std::cout << WSTOPSIG(status) << std::endl;;
  std::cout << WIFCONTINUED(status) << std::endl;;

}
