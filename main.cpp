#include <iostream>
#include <thread>
#include <windows.h>
#include <chrono>
#include <vector>
#include <atomic>
#include <condition_variable>

#include "zad1_old.h"
#include "zad1_new.h"

#include "zad2_new.h"
#include "zad2_old.h"
#include "zad2_full.h"

#include "zad3_old.h"
#include "zad3_new.h"


int main()
{
    //program1_new(); // - ok
    //program1_old(); // - ok

    //program2_full(); // - ok
    //program2_old(); // - ok
    //program2_new(); // - ok

    program3_old();

    return 0;
}
