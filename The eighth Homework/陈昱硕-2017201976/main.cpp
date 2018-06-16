#include "search_engine.h"

using namespace std;

int main(){
    SearchEngine search_engine("file_list.txt");
    for (int i = 0; i < 10; i ++)
        search_engine.Run();
    return 0;
}