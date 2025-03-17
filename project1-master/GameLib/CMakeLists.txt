project(GameLib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        ids.h
        GameView.cpp
        GameView.h
        Game.cpp
        Game.h
        Sparty.cpp
        Sparty.h
        Item.h
        Item.cpp
        ItemExample.cpp
        ItemExample.h
        ItemGrabbable.cpp
        ItemGrabbable.h
        ItemGrabbableExample.cpp
        ItemGrabbableExample.h
        Conveyor.cpp
        Conveyor.h
        LogicGate.cpp
        LogicGate.h
        OrLogicGate.cpp
        OrLogicGate.h
        Product.cpp
        Product.h
        Beam.cpp
        Beam.h
        Scoreboard.cpp
        Scoreboard.h
        Sensor.cpp
        Sensor.h
        PinOutput.h
        IDraggable.h
        PinInput.h
        PinInput.cpp
        PinOutput.cpp
        GameVisitor.cpp
        GameVisitor.h
        LevelLoader.cpp
        LevelLoader.h
        ItemVisitor.h
        ItemCounter.h
        Banner.cpp
        Banner.h
        ConveyorControlVisitor.cpp
        ConveyorControlVisitor.h
        SRLogicGate.cpp
        SRLogicGate.h
        AndLogicGate.cpp
        AndLogicGate.h
        NotLogicGate.cpp
        NotLogicGate.h
        DLogicGate.cpp
        DLogicGate.h
        ConveyorProductMoveVisitor.cpp
        ConveyorProductMoveVisitor.h
        XORLogicGate.cpp
        XORLogicGate.h
        ToggleControlPointsVisitor.h
        ItemEmpty.cpp
        OutputLogicGate.cpp
        OutputLogicGate.h
        InputLogicGate.cpp
        InputLogicGate.h
        Pin.cpp
        Pin.h
        BeamDetectionVisitor.cpp
        BeamDetectionVisitor.h
        SensorDetectionVisitor.h
        ScoreUpdateVisitor.h
        SpartyProductVisitor.h
        ProductResetVisitor.h
        ScoreboardVisitor.h
        StopConveyorVisitor.h
)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)