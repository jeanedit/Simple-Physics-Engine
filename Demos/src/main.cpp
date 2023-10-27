
#include "Ballistic.h"

using namespace std::string_literals;



int main()
{
	TimingData::Init();
	BallisticDemo bd(800, 600, "Ballistic"s);
	if (!bd.Initialize()) {
		return -1;
	}
	bd.Run();
	bd.Terminate();
    return 0;
}
