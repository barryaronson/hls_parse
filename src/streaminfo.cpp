

#include "streaminfo.h"

StreamInfo::StreamInfo(const char *attributeList) {
  const char *attribute = attributeList;
  while (*attribute) {
    const char *attributeEnd = strchr(attribute, '=');
    if (attributeEnd == nullptr) {
      return; // todo throw exception
    }
    const size_t attributeLen = attributeEnd - attribute;
    const char *value = nullptr;

    switch (*attribute) {
    case 'A':
      if ((value = compareAttribute(attribute, "AUDIO")) != nullptr) {
        attribute = value;
        std::cout << "AUDIO = " << getQuotedString(value) << std::endl;
      } else if ((value = compareAttribute(attribute, "AVERAGE-BANDWIDTH")) !=
                 nullptr) {
        attribute = value;
        std::cout << "AVERAGE-BANDWIDTH = " << getUnsignedLong(value)
                  << std::endl;
      } else {
        goto attributeError;
      }
      break;
    case 'B':
      if ((value = compareAttribute(attribute, "BANDWIDTH")) != nullptr) {
        attribute = value;
        unsigned long bandwidth = getUnsignedLong(attribute);
        std::cout << "BANDWIDTH = " << bandwidth << std::endl;
      } else {
        goto attributeError;
      }
      break;
    case 'C':
      if ((value = compareAttribute(attribute, "CLOSED-CAPTIONS")) != nullptr) {
        attribute = value; // will be a quoted string or not quoted NONE
        std::cout << "CLOSED-CAPTIONS = " << value << std::endl;
      } else if ((value = compareAttribute(attribute, "CODECS")) != nullptr) {
        attribute = value;
        std::cout << "CODECS = " << getQuotedString(value) << std::endl;
      } else {
        goto attributeError;
      }
      break;
    case 'F':
      if ((value = compareAttribute(attribute, "FRAME-RATE")) != nullptr) {
        attribute = value;
        double framerate = getDouble(value);
        std::cout << "FRAME-RATE = " << framerate << std::endl;
      } else {
        goto attributeError;
      }
      break;
    case 'H':
      attribute = getHDCPLevel(attribute);
      break;
    case 'R':
      if (strncmp(attribute, "RESOLUTION", attributeLen) == 0) {
        std::cout << "RESOLUTION" << std::endl;
      } else {
        // todo throw exception
      }
      break;
    case 'S':
      if (strncmp(attribute, "SUBTITLES", attributeLen) == 0) {
        std::cout << "SUBTITLES" << std::endl;
      } else {
        // todo throw exception
      }
      break;
    case 'V':
      if (strncmp(attribute, "VIDEO", attributeLen) == 0) {
        std::cout << "VIDEO" << std::endl;
      } else {
        // todo throw exception
      }
      break;
    attributeError:
    default:
      break;
    }

    if ((attribute = strchr(attribute, ',')) == nullptr || *attribute == '\0') {
      return;
    }
    ++attribute; // skip ','
  }
}

const char *StreamInfo::getHDCPLevel(const char *attribute) {
  const char *value = compareAttribute(attribute, "HDCP-LEVEL");

  if (value != nullptr) {
    switch (*value) {

    case 'N': {
      const char *None = "NONE";
      const size_t NoneLen = 4;

      if (strncmp(value, None, NoneLen) == 0) {
        attribute = value + NoneLen;
        std::cout << "HDCP-LEVEL = " << None << std::endl;
        break;
      } else {
        goto attributeError;
      }
    }

    case 'T': {
      const char *Type = "TYPE-";
      const size_t TypeLen = 5; // strlen(Type)
      if (strncmp(value, Type, TypeLen) == 0) {
        attribute = value + TypeLen;
        switch (*attribute) {
        case '0':
          hdcpLevel = TYPE_0;
          break;
        case '1':
          hdcpLevel = TYPE_1;
          break;
        case '\0':
        default:
          goto attributeError;
        }
        attribute++;
        break;
      } else {
        goto attributeError;
      }
    } break;
    }
  } else {
    goto attributeError;
  }

  return attribute;

attributeError:
  throw std::runtime_error("Bad HDCP-LEVEL attribute.");
  return nullptr;
}
