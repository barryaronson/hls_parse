

#include "streaminf.h"

StreamInf::StreamInf(const char *attributeList) {
  const char *attribute = attributeList;
  while (*attribute) {
    const char *attributeEnd = strchr(attribute, '=');
    if (attributeEnd == nullptr) {
      throw std::runtime_error("STREAM-INF attribute has no value");
    }
    const char *value = nullptr;

    switch (*attribute) {
    case 'A':
      if ((value = compareAttribute(attribute, "ALLOWED-CPC")) != nullptr) {
        attribute = value;
        allowedCPC = getQuotedString(value);
      } else if ((value = compareAttribute(attribute, "AUDIO")) != nullptr) {
        attribute = value;
        audio = getQuotedString(value);
      } else if ((value = compareAttribute(attribute, "AVERAGE-BANDWIDTH")) !=
                 nullptr) {
        attribute = value;
        averageBandwidth = getUnsignedLong(value);
      } else {
        goto attributeError;
      }
      break;
    case 'B':
      if ((value = compareAttribute(attribute, "BANDWIDTH")) != nullptr) {
        attribute = value;
        bandwidth = getUnsignedLong(value);
      } else {
        goto attributeError;
      }
      break;
    case 'C':
      if ((value = compareAttribute(attribute, "CLOSED-CAPTIONS")) != nullptr) {
        attribute = value; // will be a quoted string or not quoted NONE
        closedCaptions = getQuotedString(value);
      } else if ((value = compareAttribute(attribute, "CODECS")) != nullptr) {
        attribute = value;
        codecs = getQuotedString(value);
      } else {
        goto attributeError;
      }
      break;
    case 'F':
      if ((value = compareAttribute(attribute, "FRAME-RATE")) != nullptr) {
        attribute = value;
        frameRate = getDouble(value);
      } else {
        goto attributeError;
      }
      break;
    case 'H':
      if ((value = getHDCPLevel(attribute)) != nullptr) {
        attribute = value;
        // `getHDCPLevel()` sets level
      }
      break;
    case 'P':
      if ((value = compareAttribute(attribute, "PATHWAY-ID")) != nullptr) {
        attribute = value;
        pathwayID = getQuotedString(attribute);
      }
      break;
    case 'R':
      if ((value = compareAttribute(attribute, "REQ-VIDEO-LAYOUT")) !=
          nullptr) {
        attribute = value;
        reqVideoLayout = getQuotedString(attribute);
      } else if ((value = compareAttribute(attribute, "RESOLUTION")) !=
                 nullptr) {
        attribute = value;
        resolution = getQuotedString(attribute);
      } else {
        goto attributeError;
      }
      break;
    case 'S': //
      if ((value = compareAttribute(attribute, "SCORE")) != nullptr) {
        score = getDouble(value);
      } else if ((value = compareAttribute(attribute, "STABLE-VARIANT-ID")) !=
                 nullptr) {
        attribute = value;
        stableVariantID = getQuotedString(value);
      } else if ((value = compareAttribute(attribute, "SUBTITLES")) !=
                 nullptr) {
        attribute = value;
        subtitles = getQuotedString(value);
      } else if ((value = compareAttribute(attribute, "SUPPLEMENTAL-CODECS")) !=
                 nullptr) {
        attribute = value;
        supplementalCodecs = getQuotedString(value);
      } else {
        goto attributeError;
      }
      break;
    case 'V':
      if ((value = compareAttribute(attribute, "VIDEO")) != nullptr) {
        attribute = value;
        video = getQuotedString(value);
      } else if ((value = compareAttribute(attribute, "VIDEO-RANGE")) !=
                 nullptr) {
        attribute = getVideoRange(value); // todo: map to // SDR, HLG or PQ
      } else {
        goto attributeError;
      }
      break;
    attributeError:
    default:
      break;
    }

    if ((attribute = strchr(attribute, ',')) == nullptr) {
      return;
    }
    ++attribute; // skip ','
  }
}

const char *StreamInf::getHDCPLevel(const char *attribute) {
  const char *value = compareAttribute(attribute, "HDCP-LEVEL");

  if (value != nullptr) {
    switch (*value) {

    case 'N': {
      const char *None = "NONE";
      const size_t NoneLen = 4;

      if (strncmp(value, None, NoneLen) == 0) {
        attribute = value + NoneLen;
        hdcpLevel = NONE;
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
  throw std::runtime_error("Bad HDCP-LEVEL value.");
  return nullptr;
}

const char *StreamInf::getVideoRange(const char *attribute) {
  const char *value = attribute;

  switch (*value) {
  case 'S': {
    const char *sdr = "SDR";
    const size_t sdrLen = 3;

    if (strncmp(value, sdr, sdrLen) == 0) {
      attribute = value + sdrLen;
      videoRange = SDR;
      break;
    } else {
      goto attributeError;
    }
  }
  case 'H': {
    const char *hlg = "HLG";
    const size_t hlgLen = 3;

    if (strncmp(value, hlg, hlgLen) == 0) {
      attribute = value + hlgLen;
      videoRange = HLG;
      break;
    } else {
      goto attributeError;
    }
  }
  case 'P': {
    const char *pq = "PQ";
    const size_t pqLen = 2;

    if (strncmp(value, pq, pqLen) == 0) {
      attribute = value + pqLen;
      videoRange = PQ;
      break;
    } else {
      goto attributeError;
    }
  }
  }

  return attribute;

attributeError:
  throw std::runtime_error("Bad VIDEO-RANGE value.");
  return nullptr;
}
