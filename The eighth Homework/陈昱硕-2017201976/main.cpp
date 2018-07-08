#include "search_engine.h"

using namespace std;

int main(){
    SearchEngine search_engine("file_list.txt");
    while (true)
        search_engine.Run();
    return 0;
}
