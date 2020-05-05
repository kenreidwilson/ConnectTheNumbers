#include "UserSettings.h"

#include "FileIOUtility.h"
using namespace Utility;

#include <sstream>
#include <iostream>

namespace Model
{
    UserSettings::UserSettings()
    {
        this->userSettingsFilePath = "UserSettings.txt";
        this->userCellColorPreferenceIdentifier = "cell_color";
        this->userLabelColorPreferenceIdentifier = "label_color";
        try
        {
            this->userSettingsMap = parseUserSettingsFromFile();
        }
        catch (invalid_argument)
        {
            FileIOUtility::initializeFile(this->userSettingsFilePath);
        }

    }

    UserSettings::~UserSettings() {}

    int UserSettings::getUsersCellColorPreference()
    {
        return this->userSettingsMap[this->userCellColorPreferenceIdentifier];
    }

    void UserSettings::setUsersCellColorPreference(int color)
    {
        this->userSettingsMap[this->userCellColorPreferenceIdentifier] = color;
    }

    int UserSettings::getUsersLabelColorPreference()
    {
        return this->userSettingsMap[this->userLabelColorPreferenceIdentifier];
    }

    void UserSettings::setUsersLabelColorPreference(int color)
    {
        this->userSettingsMap[this->userLabelColorPreferenceIdentifier] = color;
    }

    void UserSettings::saveSettings()
    {
        stringstream settingsFileLine;
        vector<string> settingsFileLines;
        for (const auto &settingsPair : this->userSettingsMap)
        {
            settingsFileLine.str("");
            settingsFileLine << settingsPair.first;
            settingsFileLine << this->settingsFileDelimiter;
            settingsFileLine << settingsPair.second;
            settingsFileLines.push_back(settingsFileLine.str());
        }
        FileIOUtility::writeLines(this->userSettingsFilePath, settingsFileLines);
    }

    map<string, int> UserSettings::parseUserSettingsFromFile()
    {
        map<string, int> parsedUserSettings;
        bool hasPassedDelimiter;
        string settingsIdentifier;
        string settingsValueString;
        for (string settingsFileLine : FileIOUtility::readLines(this->userSettingsFilePath))
        {
            settingsIdentifier = "";
            settingsValueString = "";
            hasPassedDelimiter = false;
            for (const char& currentChar : settingsFileLine)
            {
                if (currentChar == this->settingsFileDelimiter)
                {
                    hasPassedDelimiter = true;
                }
                else if (hasPassedDelimiter)
                {
                    settingsValueString += currentChar;
                }
                else
                {
                    settingsIdentifier += currentChar;
                }
            }
            if (settingsIdentifier == "" || !hasPassedDelimiter)
            {
                continue;
            }
            int settingsValue;
            try
            {
                settingsValue = stoi(settingsValueString);
            }
            catch (invalid_argument)
            {
                continue;
            }
            parsedUserSettings[settingsIdentifier] = settingsValue;
        }
        return parsedUserSettings;
    }
}

