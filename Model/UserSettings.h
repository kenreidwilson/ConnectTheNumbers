#ifndef USERSETTINGS_H
#define USERSETTINGS_H

#include <string>
#include <map>
using namespace std;

namespace Model
{
/**
* Tracks and persists a User's settings.
*/
class UserSettings
{
    public:
        /**
        * Constructs a UserSettings object.
        */
        UserSettings();

        /**
        * Destructs a UserSettings object.
        */
        virtual ~UserSettings();

        /**
        * Returns a User's cell color preference setting.
        *
        * @return a User's color preference..
        */
        int getUsersCellColorPreference();

        /**
        * Sets and persists a user's cell color preference setting.
        *
        * @param color a user's color preference.
        */
        void setUsersCellColorPreference(int color);

                /**
        * Returns a User's label color preference setting.
        *
        * @return a User's color preference..
        */
        int getUsersLabelColorPreference();

        /**
        * Sets and persists a user's label color preference setting.
        *
        * @param color a user's color preference.
        */
        void setUsersLabelColorPreference(int color);

        /**
        * Persists a user's settings to the userSettingsFile.
        */
        void saveSettings();
    private:

        /**
        * A filepath leading to the file that stores a user's settings.
        */
        string userSettingsFilePath;

        /**
        * The delimiter that seperates a user's setting and its identifier.
        */
        char settingsFileDelimiter = '=';

        /**
        * The string identifier that represents a user's label color preference.
        */
        string userLabelColorPreferenceIdentifier;

        /**
        * The string identifier that represents a user's cell color preference.
        */
        string userCellColorPreferenceIdentifier;

        /**
        * A map that contains a user's settings.
        */
        map<string, int> userSettingsMap;

        /**
        * Populates the userSettingsMap from the userSettingsFile.
        */
        map<string, int> parseUserSettingsFromFile();
};
}
#endif // USERSETTINGS_H
