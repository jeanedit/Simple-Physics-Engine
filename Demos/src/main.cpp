
#include "Ballistic.h"
#include "Fireworks.h"
using namespace std::string_literals;



int main()
{
	TimingData::Init();

	//BallisticDemo bd(800, 600, "Ballistic"s);
	//if (!bd.Initialize()) {
	//	return -1;
	//}
	//bd.Run();
	//bd.Terminate();

	FireworksDemo fd(800, 600, "Fireworks"s);
	if (!fd.Initialize()) {
		return -1;
	}
	fd.Run();
	fd.Terminate();
	return 0;
}
