# Source files

# Test files
target_sources(${PROJECT_NAME} PRIVATE
    "src/openNetworkHMI_test.cpp"
	"src/tests/driver/DriverTestsFixtures.h"
	"src/tests/driver/DriverTypesTests.h"
	"src/tests/driver/SHM/ShmDriverRealTests.h"
	"src/tests/driver/SHM/ShmDriverWordTests.h"
	"src/tests/driver/SHM/ShmDriverByteTests.h"
	"src/tests/driver/SHM/ShmDriverTestsFixtures.h"
	"src/tests/driver/SHM/ShmDriverIntTests.h"
	"src/tests/driver/SHM/ShmDriverBitTests.h"
	"src/tests/driver/SHM/ShmDriverDWordTests.h"
	"src/tests/driver/ProcessWriterTests.h"
	"src/tests/driver/ProcessReaderTests.h"
	"src/tests/driver/Modbus/ModbusDriverRealTests.h"
	"src/tests/driver/Modbus/ModbusDriverByteTests.h"
	"src/tests/driver/Modbus/ModbusDriverIntTests.h"
	"src/tests/driver/Modbus/ModbusDriverWordTests.h"
	"src/tests/driver/Modbus/ModbusDriverDWordTests.h"
	"src/tests/driver/Modbus/ModbusDriverTestsFixtures.h"
	"src/tests/driver/Modbus/ModbusDriverBitTests.h"
	"src/tests/utils/MutexTestsFixtures.h"
	"src/tests/utils/MutexTests.h"
	"src/tests/utils/LoggerTests.h"
	"src/tests/utils/StringUtilsTests.h"
	"src/tests/utils/LoggerTestsFixtures.h"
	"src/tests/utils/DelayTests.h"
	"src/tests/utils/CycleTimeTests.h"
	"src/tests/utils/GuardDataControllerTests.h"
	"src/tests/testGlobalData.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsDWord.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsWord.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsByte.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsInt.h"
	"src/tests/db/objs/ScriptItemTestsFixtures.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsBit.h"
	"src/tests/db/objs/DriverConnectionTests.h"
	"src/tests/db/objs/TagTests.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsReal.h"
	"src/tests/db/objs/TagLoggerItemTestsFixtures.h"
	"src/tests/db/objs/AlarmDefinitionItemTests.h"
	"src/tests/db/objs/TagLoggerItemTests.h"
	"src/tests/db/objs/AlarmDefinitionItemTestsFixtures.h"
	"src/tests/db/objs/ScriptItemTests.h"
)

# Program files to test
target_sources(${PROJECT_NAME} PRIVATE
    "../../src/onh/driver/DriverBuffer.h"
	"../../src/onh/driver/ProcessWriter.cpp"
	"../../src/onh/driver/ProcessUtils.h"
	"../../src/onh/driver/DriverException.cpp"
	"../../src/onh/driver/DriverManager.h"
	"../../src/onh/driver/Driver.cpp"
	"../../src/onh/driver/ProcessUpdater.cpp"
	"../../src/onh/driver/ProcessDataTypes.h"
	"../../src/onh/driver/DriverException.h"
	"../../src/onh/driver/ProcessUpdaterData.h"
	"../../src/onh/driver/DriverBufferUpdater.h"
	"../../src/onh/driver/DriverManager.cpp"
	"../../src/onh/driver/DriverProcessReader.h"
	"../../src/onh/driver/DriverBufferUpdater.cpp"
	"../../src/onh/driver/ProcessUpdater.h"
	"../../src/onh/driver/DriverProcessReader.cpp"
	"../../src/onh/driver/DriverUtils.h"
	"../../src/onh/driver/SHM/ShmProcessUpdater.cpp"
	"../../src/onh/driver/SHM/ShmProcessReader.h"
	"../../src/onh/driver/SHM/ShmProcessReader.cpp"
	"../../src/onh/driver/SHM/ShmProcessWriter.h"
	"../../src/onh/driver/SHM/ShmProcessUpdater.h"
	"../../src/onh/driver/SHM/ShmProcessWriter.cpp"
	"../../src/onh/driver/SHM/ShmProcessData.cpp"
	"../../src/onh/driver/SHM/sMemory.h"
	"../../src/onh/driver/SHM/processData.h"
	"../../src/onh/driver/SHM/ShmProcessData.h"
	"../../src/onh/driver/SHM/ShmDriver.cpp"
	"../../src/onh/driver/SHM/ShmDriver.h"
	"../../src/onh/driver/SHM/sCommands.h"
	"../../src/onh/driver/DriverProcessUpdater.h"
	"../../src/onh/driver/DriverRegisterTypes.h"
	"../../src/onh/driver/ProcessReader.h"
	"../../src/onh/driver/ProcessReader.cpp"
	"../../src/onh/driver/DriverUtils.cpp"
	"../../src/onh/driver/ProcessUtils.cpp"
	"../../src/onh/driver/DriverProcessWriter.cpp"
	"../../src/onh/driver/Modbus/ModbusUpdater.cpp"
	"../../src/onh/driver/Modbus/ModbusProcessWriter.cpp"
	"../../src/onh/driver/Modbus/ModbusProcessUpdater.h"
	"../../src/onh/driver/Modbus/modbusmaster.cpp"
	"../../src/onh/driver/Modbus/modbusmasterCfg.h"
	"../../src/onh/driver/Modbus/ModbusProcessData.cpp"
	"../../src/onh/driver/Modbus/ModbusDriver.cpp"
	"../../src/onh/driver/Modbus/modbusmaster.h"
	"../../src/onh/driver/Modbus/ModbusUtils.cpp"
	"../../src/onh/driver/Modbus/modbusexception.h"
	"../../src/onh/driver/Modbus/ModbusDriver.h"
	"../../src/onh/driver/Modbus/ModbusUtils.h"
	"../../src/onh/driver/Modbus/ModbusUpdater.h"
	"../../src/onh/driver/Modbus/modbusexception.cpp"
	"../../src/onh/driver/Modbus/ModbusRegisters.h"
	"../../src/onh/driver/Modbus/ModbusProcessData.h"
	"../../src/onh/driver/Modbus/ModbusProcessReader.h"
	"../../src/onh/driver/Modbus/ModbusProcessReader.cpp"
	"../../src/onh/driver/Modbus/ModbusProcessWriter.h"
	"../../src/onh/driver/Modbus/ModbusProcessUpdater.cpp"
	"../../src/onh/driver/Driver.h"
	"../../src/onh/driver/DriverBuffer.cpp"
	"../../src/onh/driver/DriverProcessWriter.h"
	"../../src/onh/driver/DriverProcessUpdater.cpp"
	"../../src/onh/driver/DriverBufferUpdaterData.h"
	"../../src/onh/driver/ProcessWriter.h"
	"../../src/onh/utils/StringUtils.h"
	"../../src/onh/utils/DateUtils.cpp"
	"../../src/onh/utils/Logger.h"
	"../../src/onh/utils/MutexAccess.h"
	"../../src/onh/utils/StringUtils.cpp"
	"../../src/onh/utils/CycleTime.h"
	"../../src/onh/utils/MutexContainer.h"
	"../../src/onh/utils/CycleTime.cpp"
	"../../src/onh/utils/Exception.cpp"
	"../../src/onh/utils/Exception.h"
	"../../src/onh/utils/MutexAccess.cpp"
	"../../src/onh/utils/Delay.cpp"
	"../../src/onh/utils/Logger.cpp"
	"../../src/onh/utils/DateUtils.h"
	"../../src/onh/utils/GuardDataContainer.h"
	"../../src/onh/utils/GuardDataController.h"
	"../../src/onh/utils/MutexContainer.cpp"
	"../../src/onh/utils/Delay.h"
	"../../src/onh/db/TagLoggerDB.cpp"
	"../../src/onh/db/DBManager.cpp"
	"../../src/onh/db/DBManager.h"
	"../../src/onh/db/ScriptDB.cpp"
	"../../src/onh/db/DBResult.cpp"
	"../../src/onh/db/ScriptDB.h"
	"../../src/onh/db/DB.h"
	"../../src/onh/db/ParserDB.cpp"
	"../../src/onh/db/Config.h"
	"../../src/onh/db/DBCredentials.h"
	"../../src/onh/db/TagLoggerDB.h"
	"../../src/onh/db/ParserDB.h"
	"../../src/onh/db/DBResult.h"
	"../../src/onh/db/DB.cpp"
	"../../src/onh/db/AlarmingDB.cpp"
	"../../src/onh/db/Config.cpp"
	"../../src/onh/db/objs/Tag.cpp"
	"../../src/onh/db/objs/DriverConnection.cpp"
	"../../src/onh/db/objs/ScriptItem.h"
	"../../src/onh/db/objs/DriverConnection.h"
	"../../src/onh/db/objs/TagLoggerItem.h"
	"../../src/onh/db/objs/TagException.cpp"
	"../../src/onh/db/objs/AlarmException.h"
	"../../src/onh/db/objs/AlarmException.cpp"
	"../../src/onh/db/objs/TagException.h"
	"../../src/onh/db/objs/AlarmDefinitionItem.h"
	"../../src/onh/db/objs/TagLoggerItem.cpp"
	"../../src/onh/db/objs/ScriptItem.cpp"
	"../../src/onh/db/objs/ScriptException.h"
	"../../src/onh/db/objs/AlarmDefinitionItem.cpp"
	"../../src/onh/db/objs/Tag.h"
	"../../src/onh/db/objs/ScriptException.cpp"
	"../../src/onh/db/AlarmingDB.h"
	"../../src/onh/db/DBException.cpp"
	"../../src/onh/db/DBException.h"
)