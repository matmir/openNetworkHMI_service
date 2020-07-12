/**
 * This file is part of openNetworkHMI.
 * Copyright (c) 2020 Mateusz Mirosławski.
 *
 * openNetworkHMI is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * openNetworkHMI is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with openNetworkHMI.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "CommandParser.h"
#include <sstream>
#include "../../../db/objs/Tag.h"
#include "../../../utils/StringUtils.h"

using namespace onh;

CommandParser::CommandParser(const ProcessReader& pr,
								const ProcessWriter& pw,
								const DBCredentials& dbc,
								const ThreadCycleControllers& cc,
								const ThreadExitController &thEC,
								int connDescriptor):
	cycleController(cc)
{
    // Process reader
    prReader = new ProcessReader(pr);

    // Process writer
    prWriter = new ProcessWriter(pw);

    // Thread controller
    thExitController = new ThreadExitController(thEC);

    // DB access
    db = new ParserDB(dbc);

    // Create logger
    std::stringstream s;
    s << "parser_th_" << connDescriptor << " ";
    log = new Logger("parser", s.str());
}

CommandParser::~CommandParser()
{
    if (prReader)
        delete prReader;
    if (prWriter)
        delete prWriter;
    if (thExitController)
        delete thExitController;
    if (db)
        delete db;

    if (log) {
        delete log;
    }
}

std::string CommandParser::getReply(std::string query) {

    std::string s;
    std::vector<std::string> v;

    parserCMD cmd;

    try {
        // Check readers
        if (!prReader)
            throw Exception("No process reader object", "CommandParser::getReply");
        if (!prWriter)
            throw Exception("No process writer object", "CommandParser::getReply");

        // Update process reader
		prReader->updateProcessData();

        // Check if there is query string
        if (query.length() == 0)
			throw CommandParserException(CommandParserException::WRONG_DATA, "Query string is empty", "CommandParser::getReply");

        // Explode command and data
        v = StringUtils::explode(query,'|');

        // Check exploded data count
        if (v.size() != 2)
            throw CommandParserException(CommandParserException::WRONG_DATA_COUNT, "Wrong exploded data count", "CommandParser::getReply");

        // Parse command number
        cmd = parseCMD(v[0]);

        // Parse whole command
        s = parseCommand(cmd, v[1]);


    } catch(CommandParserException &e) {
        log->write(e.what());

        switch (e.getType()){

            case CommandParserException::NONE: s = replyError(INTERNAL_ERR); break;
            case CommandParserException::WRONG_DATA: s = replyError(UNKNOWN_CMD); break;
            case CommandParserException::WRONG_DATA_COUNT: s = replyError(UNKNOWN_CMD); break;
            case CommandParserException::CONVERSION_COMMAND: s = replyError(UNKNOWN_CMD); break;
            case CommandParserException::UNKNOWN_COMMAND: s = replyError(UNKNOWN_CMD); break;

        }
    } catch (TagException &e) {
        log->write(e.what());

        switch (e.getType()) {

            case TagException::NONE: s = replyError(INTERNAL_ERR); break;
            case TagException::WRONG_ID: s = replyError(UNKNOWN_CMD); break;
            case TagException::WRONG_NAME: s = replyError(UNKNOWN_CMD); break;
            case TagException::WRONG_TYPE: s = replyError(WRONG_TAG_TYPE); break;
            case TagException::WRONG_AREA: s = replyError(WRONG_TAG_AREA); break;
            case TagException::BYTE_ADDRESS_OUT_OF_RANGE: s = replyError(WRONG_ADDR); break;
            case TagException::BIT_ADDRESS_OUT_OF_RANGE: s = replyError(WRONG_ADDR); break;
            case TagException::NOT_EXIST: s = replyError(NOT_EXIST); break;

        }
    } catch (Exception &e) {
    	log->write(e.what());

        s = replyError(INTERNAL_ERR);
    }

    return s;

}

bool CommandParser::checkCMD(int cmdNr) {

    bool ret = false;

    switch (cmdNr) {

        case GET_BIT: ret = true; break;
        case SET_BIT: ret = true; break;
        case RESET_BIT: ret = true; break;
        case INVERT_BIT: ret = true; break;
        case GET_BITS: ret = true; break;
        case SET_BITS: ret = true; break;
        case GET_BYTE: ret = true; break;
        case WRITE_BYTE: ret = true; break;
        case GET_WORD: ret = true; break;
        case WRITE_WORD: ret = true; break;
        case GET_DWORD: ret = true; break;
        case WRITE_DWORD: ret = true; break;
        case GET_INT: ret = true; break;
        case WRITE_INT: ret = true; break;
        case GET_REAL: ret = true; break;
        case WRITE_REAL: ret = true; break;
        case MULTI_CMD: ret = true; break;
        case ACK_ALARM: ret = true; break;
        case GET_THREAD_CYCLE_TIME: ret = true; break;
        case EXIT_APP: ret = true; break;

    }

    return ret;
}

parserCMD CommandParser::parseCMD(std::string str) {

    if (str.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::parseCMD");

    int val = 0;

    std::istringstream iss(str);
    iss >> val;

    // Check value
    if (!checkCMD(val))
        throw CommandParserException(CommandParserException::UNKNOWN_COMMAND, "Unknown command: "+str, "CommandParser::parseCMD");

    return (parserCMD)val;
}

std::string CommandParser::replyOK(parserCMD cmd, std::string data) {

    std::stringstream s;

    s << cmd << "|";

    // Check data string
    if (data.length() == 0) {
        s << OK;
    } else {
        s << data;
    }

    return s.str();
}

std::string CommandParser::replyOK(parserCMD cmd, std::vector<bool> data) {

    std::stringstream s;

    s << cmd << '|';

    // Check data
    if (data.size() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::replyOK (vector BOOL)");

    for (unsigned int i=0; i<data.size(); ++i) {

        s << ((data[i])?("1"):("0"));

        if (i < data.size()-1) {
            s << ',';
        }

    }

    return s.str();
}

std::string CommandParser::replyOK(BYTE data) {

    std::stringstream s;

    s << GET_BYTE << '|' << (int)data;

    return s.str();
}

std::string CommandParser::replyOK(WORD data) {

    std::stringstream s;

    s << GET_WORD << '|' << (WORD)data;

    return s.str();
}

std::string CommandParser::replyOK(DWORD data) {

    std::stringstream s;

    s << GET_DWORD << '|' << (DWORD)data;

    return s.str();
}

std::string CommandParser::replyOK(int data) {

    std::stringstream s;

    s << GET_INT << '|' << (int)data;

    return s.str();
}

std::string CommandParser::replyOK(float data) {

    std::stringstream s;

    s << GET_REAL << '|' << (float)data;

    return s.str();
}

std::string CommandParser::replyOK(std::vector<std::string> data) {

    std::stringstream s;

    s << MULTI_CMD << '|';

    // Check data
    if (data.size() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::replyOK (MULTI_CMD)");

    for (unsigned int i=0; i<data.size(); ++i) {

        // Replace delimiter
        data[i] = StringUtils::replaceChar(data[i], '|', '?');

        s << data[i];

        if (i < data.size()-1) {
            s << '!';
        }

    }

    return s.str();
}

std::string CommandParser::replyOK(CycleTimeData tpcUpdater,
                                CycleTimeData tpcLogger,
								CycleTimeData tpcLoggerWriter,
                                CycleTimeData tpcAlarming,
                                CycleTimeData tpcScript,
                                CycleTimeData tpcPolling)
{
    std::stringstream s;

    s << GET_THREAD_CYCLE_TIME << '|';
    s << "Updater:"  << tpcUpdater.min << '?' << tpcUpdater.max << '?' << tpcUpdater.current << '!';
    s << "Polling:"  << tpcPolling.min << '?' << tpcPolling.max << '?' << tpcPolling.current << '!';
    s << "Logger:"  << tpcLogger.min << '?' << tpcLogger.max << '?' << tpcLogger.current << '!';
    s << "LoggerWriter:"  << tpcLoggerWriter.min << '?' << tpcLoggerWriter.max << '?' << tpcLoggerWriter.current << '!';
    s << "Alarming:"  << tpcAlarming.min << '?' << tpcAlarming.max << '?' << tpcAlarming.current << '!';
    s << "Script:"  << tpcScript.min << '?' << tpcScript.max << '?' << tpcScript.current;

    return s.str();
}

std::string CommandParser::replyError(parserReply rp) {

    std::stringstream s;

    s << NOK << "|" << rp;

    return s.str();
}

std::string CommandParser::CMD_GET_BIT(std::string data) {

    std::string s;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_BIT");

    // Get Tag
    Tag t(db->getTag(data));

    // Get bit value
    bool v = prReader->getBitValue(t);

    // Prepare answer
    s = (v)?("1"):("0");

    return replyOK(GET_BIT, s);
}

std::string CommandParser::CMD_SET_BIT(std::string data) {

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_SET_BIT");

    // Get Tag
    Tag t(db->getTag(data));

    // Set bit
    prWriter->setBit(t);

    return replyOK(SET_BIT);
}

std::string CommandParser::CMD_RESET_BIT(std::string data) {

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_RESET_BIT");

    // Get Tag
    Tag t(db->getTag(data));

    // Reset bit
    prWriter->resetBit(t);

    return replyOK(RESET_BIT);
}

std::string CommandParser::CMD_INVERT_BIT(std::string data) {

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_RESET_BIT");

    // Get Tag
    Tag t(db->getTag(data));

    // Invert bit
    prWriter->invertBit(t);

    return replyOK(INVERT_BIT);
}

std::string CommandParser::CMD_GET_BITS(std::string data) {

    std::string s;
    std::vector<std::string> v;
    std::vector<Tag> vTag;
    std::vector<bool> TagValues;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_BITS");

    // Explode tag names
    v = StringUtils::explode(data, ',');
    if (v.size() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_GET_BITS");

    // Read tag data from DB
    vTag = db->getTags(v);

    // Get bits values
    TagValues = prReader->getBitsValue(vTag);

    if (TagValues.size() != v.size())
        throw CommandParserException(CommandParserException::WRONG_DATA_COUNT, "Not all data read", "CommandParser::CMD_GET_BITS");

    if (TagValues.size() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data from controller", "CommandParser::CMD_GET_BITS");

    return replyOK(GET_BITS, TagValues);
}

std::string CommandParser::CMD_SET_BITS(std::string data) {

    std::vector<std::string> v;
    std::vector<Tag> vTag;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_SET_BITS");

    // Explode tag names
    v = StringUtils::explode(data, ',');
    if (v.size() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_SET_BITS");

    // Read tag data from DB
    vTag = db->getTags(v);

    // Set bits
    prWriter->setBits(vTag);

    return replyOK(SET_BITS);
}

std::string CommandParser::CMD_GET_BYTE(std::string data) {

    std::stringstream s;
    BYTE v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_BYTE");

    // Read Tag data from DB
    Tag t(db->getTag(data));

    // Get Byte from controller
    v = prReader->getByte(t);

    return replyOK(v);
}

std::string CommandParser::CMD_WRITE_BYTE(std::string data) {

    std::vector<std::string> v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_WRITE_BYTE");

    // Explode command on tag and value
    v = StringUtils::explode(data, ',');
    if (v.size() != 2)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_WRITE_BYTE");

    // Read Tag data from DB
    Tag t(db->getTag(v[0]));

    // Prepare value
    BYTE val;
    WORD cv;
    std::istringstream iss(v[1]);
    iss >> cv;
    val = cv;

    // Write byte
    prWriter->writeByte(t, val);

    return replyOK(WRITE_BYTE);
}

std::string CommandParser::CMD_GET_WORD(std::string data) {

    std::stringstream s;
    WORD w;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_WORD");

    // Read Tag data from DB
    Tag t(db->getTag(data));

    // Get Word from controller
    w = prReader->getWord(t);

    return replyOK(w);
}

std::string CommandParser::CMD_WRITE_WORD(std::string data) {

    std::vector<std::string> v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_WRITE_WORD");

    // Explode command on tag and value
    v = StringUtils::explode(data, ',');
    if (v.size() != 2)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_WRITE_WORD");

    // Read Tag data from DB
    Tag t(db->getTag(v[0]));

    // Prepare value
    WORD val;
    std::istringstream iss(v[1]);
    iss >> val;

    // Write byte
    prWriter->writeWord(t, val);

    return replyOK(WRITE_WORD);
}

std::string CommandParser::CMD_GET_DWORD(std::string data) {

    std::stringstream s;
    DWORD dw;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_DWORD");

    // Read Tag data from DB
    Tag t(db->getTag(data));

    // Get Word from controller
    dw = prReader->getDWord(t);

    return replyOK(dw);
}

std::string CommandParser::CMD_WRITE_DWORD(std::string data) {

    std::vector<std::string> v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_WRITE_DWORD");

    // Explode command on tag and value
    v = StringUtils::explode(data, ',');
    if (v.size() != 2)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_WRITE_DWORD");

    // Read Tag data from DB
    Tag t(db->getTag(v[0]));

    // Prepare value
    DWORD val;
    std::istringstream iss(v[1]);
    iss >> val;

    // Write byte
    prWriter->writeDWord(t, val);

    return replyOK(WRITE_DWORD);
}

std::string CommandParser::CMD_GET_INT(std::string data) {

    std::stringstream s;
    int v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_INT");

    // Read Tag data from DB
    Tag t(db->getTag(data));

    // Get INT from controller
    v = prReader->getInt(t);

    return replyOK(v);
}

std::string CommandParser::CMD_WRITE_INT(std::string data) {

    std::vector<std::string> v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_WRITE_INT");

    // Explode command on tag and value
    v = StringUtils::explode(data, ',');
    if (v.size() != 2)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_WRITE_INT");

    // Read Tag data from DB
    Tag t(db->getTag(v[0]));

    // Prepare value
    int val;
    std::istringstream iss(v[1]);
    iss >> val;

    // Write byte
    prWriter->writeInt(t, val);

    return replyOK(WRITE_INT);
}

std::string CommandParser::CMD_GET_REAL(std::string data) {

    float f;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_REAL");

    // Read Tag data from DB
    Tag t(db->getTag(data));

    // Get INT from controller
    f = prReader->getReal(t);

    return replyOK(f);
}

std::string CommandParser::CMD_WRITE_REAL(std::string data) {

    std::vector<std::string> v;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_WRITE_REAL");

    // Explode command on tag and value
    v = StringUtils::explode(data, ',');
    if (v.size() != 2)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No valid data", "CommandParser::CMD_WRITE_REAL");

    // Read Tag data from DB
    Tag t(db->getTag(v[0]));

    // Prepare value
    float val;
    std::istringstream iss(v[1]);
    iss >> val;

    // Write byte
    prWriter->writeReal(t, val);

    return replyOK(WRITE_REAL);
}

std::string CommandParser::CMD_MULTI_CMD(std::string data) {

    std::vector<std::string> v;
    std::vector<std::string> cmdReply;
    std::string cmd;
    std::stringstream s;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_MULTI_CMD");

    // Explode string on commands
    v = StringUtils::explode(data, '!');

    // Check commands
    if (v.size() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No commands", "CommandParser::CMD_MULTI_CMD");

    // Iterate all commands
    for (unsigned int i=0; i<v.size(); ++i) {

        // Get one command - replace delimiter
        cmd = StringUtils::replaceChar(v[i], '?', '|');

        // Get command reply
        cmdReply.push_back(getReplyFromMultiCMD(cmd));

    }

    return replyOK(cmdReply);
}

std::string CommandParser::getReplyFromMultiCMD(const std::string& cmd) {

    std::vector<std::string> v;
    std::string s;

    parserCMD pcmd;

    // Explode command and data
    v = StringUtils::explode(cmd,'|');

    // Check exploded data count
    if (v.size() != 2)
        throw CommandParserException(CommandParserException::WRONG_DATA_COUNT, "Wrong exploded data count", "CommandParser::getReplyFromMultiCMD");

    // Parse command number
    pcmd = parseCMD(v[0]);

    // Check if there is no multi cmd inside muti cmd - We are using recursion!!
    if (pcmd == MULTI_CMD)
        throw CommandParserException(CommandParserException::UNKNOWN_COMMAND, "Multi command inside multi command", "CommandParser::getReplyFromMultiCMD");

    if (pcmd == GET_THREAD_CYCLE_TIME)
        throw CommandParserException(CommandParserException::UNKNOWN_COMMAND, "Can not call GET_THREAD_CYCLE_TIME inside multi command", "CommandParser::getReplyFromMultiCMD");

    // Parse whole command (recursion)
    return parseCommand(pcmd, v[1]);
}

std::string CommandParser::CMD_ACK_ALARM(std::string data) {

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_ACK_ALARM");

    // Get pending alaram identifier
    unsigned int paid = 0;
    std::istringstream iss(data);
    iss >> paid;

    // Acknowledge alarm
    db->getAlarmDB().ackAlarm(paid);

    return replyOK(ACK_ALARM);
}

std::string CommandParser::CMD_GET_THREAD_CYCLE_TIME(std::string data) {

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_GET_THREAD_CYCLE_TIME");

    if (data != "1")
        throw CommandParserException(CommandParserException::WRONG_DATA, "Wrong data", "CommandParser::CMD_GET_THREAD_CYCLE_TIME");

    // Cycle times structures
    CycleTimeData UpdaterCT, LoggerCT, LoggerWriterCT, AlarmingCT, ScriptCT, PollingCT;

    // Get cycle times
    UpdaterCT = cycleController.cUpdater.getCycleTime();
    LoggerCT = cycleController.cLogger.getCycleTime();
    LoggerWriterCT = cycleController.cLoggerWriter.getCycleTime();
    AlarmingCT = cycleController.cAlarming.getCycleTime();
    ScriptCT = cycleController.cScript.getCycleTime();
    PollingCT = cycleController.cDriverPolling.getCycleTime();

    return replyOK(UpdaterCT, LoggerCT, LoggerWriterCT, AlarmingCT, ScriptCT, PollingCT);
}

std::string CommandParser::CMD_EXIT_APP(std::string data) {

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::CMD_EXIT_APP");

    if (data != "1")
        throw CommandParserException(CommandParserException::WRONG_DATA, "Wrong data", "CommandParser::CMD_EXIT_APP");

    // Exit application
    thExitController->exit("CMD_EXIT_APP from socket client");

    return replyOK(EXIT_APP);
}

std::string CommandParser::parseCommand(parserCMD cmd, std::string data) {

    std::string ret;

    // Check data string
    if (data.length() == 0)
        throw CommandParserException(CommandParserException::WRONG_DATA, "No data", "CommandParser::parseCommand");

    // Execute command
    switch (cmd) {
        case GET_BIT: ret = CMD_GET_BIT(data); break;
        case SET_BIT: ret = CMD_SET_BIT(data); break;
        case RESET_BIT: ret = CMD_RESET_BIT(data); break;
        case INVERT_BIT: ret = CMD_INVERT_BIT(data); break;
        case GET_BITS: ret = CMD_GET_BITS(data); break;
        case SET_BITS: ret = CMD_SET_BITS(data); break;
        case GET_BYTE: ret = CMD_GET_BYTE(data); break;
        case WRITE_BYTE: ret = CMD_WRITE_BYTE(data); break;
        case GET_WORD: ret = CMD_GET_WORD(data); break;
        case WRITE_WORD: ret = CMD_WRITE_WORD(data); break;
        case GET_DWORD: ret = CMD_GET_DWORD(data); break;
        case WRITE_DWORD: ret = CMD_WRITE_DWORD(data); break;
        case GET_INT: ret = CMD_GET_INT(data); break;
        case WRITE_INT: ret = CMD_WRITE_INT(data); break;
        case GET_REAL: ret = CMD_GET_REAL(data); break;
        case WRITE_REAL: ret = CMD_WRITE_REAL(data); break;
        case MULTI_CMD: ret = CMD_MULTI_CMD(data); break;
        case ACK_ALARM: ret = CMD_ACK_ALARM(data); break;
        case GET_THREAD_CYCLE_TIME: ret = CMD_GET_THREAD_CYCLE_TIME(data); break;
        case EXIT_APP: ret = CMD_EXIT_APP(data); break;
    }

    return ret;
}
