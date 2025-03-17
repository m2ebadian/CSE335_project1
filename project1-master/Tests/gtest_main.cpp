/**
 * @file gtest_main.cpp
 * @author Conner O'Sullivan
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filefn.h>

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}
