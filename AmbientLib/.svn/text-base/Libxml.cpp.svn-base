/*
 * Original: readier1.c from LibXML
 *
 * adapted by Markus Waltl (2008-2010)
 * changed by Benjamin Rainer (2011 - 2012) to support memory locations
 *
 */
#include "stdafx.h"
#include <stdio.h>
#include <algorithm>
#include "Libxml.h"
#include "typedef.h"

#ifdef LIBXML_READER_ENABLED

/**
 * processNode:
 * @reader: the xmlReader
 *
 * Dump information about the current node
 */
void Libxml::processNode(xmlTextReaderPtr reader) {
    const xmlChar *name;
    int iType = -1;

    name = xmlTextReaderConstName(reader);
    if (name == NULL || name[0] == '#')
		return;

	std::string name2 = (const char*)name;
	int pos = name2.find(":");
	name = xmlStrsub(name, pos+1, xmlStrlen(name));


    if (xmlTextReaderNodeType(reader) == XML_READER_TYPE_END_ELEMENT)
    {
		if (strcmp((const char*)name, LIBXML_GOE) == 0)
		{
			m_curTime = 0;
			m_anchorElement = false;
		}
    }

    if (xmlTextReaderNodeType(reader) == XML_ELEMENT_NODE)
    {
		if (strcmp((const char*)name, LIBXML_SEM) == 0)
			iType = 0;
		else if (strcmp((const char*)name, LIBXML_GOE) == 0)
			iType = 1;
		else if (strcmp((const char*)name, LIBXML_EFFECT) == 0)
			iType = 2;

		while (xmlTextReaderMoveToNextAttribute(reader))
		{
			xmlChar* attr = xmlTextReaderName(reader);

			// needed for removing namespace
			std::string attr2 = (const char*)attr;
			pos = attr2.find(":");
			attr = xmlStrsub(attr, pos+1, xmlStrlen(attr));

			xmlChar* value = xmlTextReaderValue(reader);

			// needed for removing namespace except if location is given
			if (strcmp((const char*)attr, LIBXML_TYPE) == 0)
			{
				attr2 = (const char*)value;
				pos = attr2.find(":");
				value = xmlStrsub(value, pos+1, xmlStrlen(value));
			}
			
			if (iType == 0) // SEM
			{
				if (strcmp((const char*)attr, LIBXML_TIMESCALE) == 0)
				{
					const char* val = (const char*)value;
					long int lVal = atol(val);
					m_timeScale = lVal;
				}
			}
			else if (iType == 1) // GroupOfEffects
			{
				if (strcmp((const char*)attr, LIBXML_ANCHORELEMENT) == 0)
				{
					const char* val = (const char*)value;
					if (strcmp(val, "true") == 0)
						m_anchorElement = true;
					else
						m_anchorElement = false;
				}
				else if (strcmp((const char*)attr, LIBXML_PTS) == 0)
				{
					const char* val = (const char*)value;
					long int lVal = atol(val);

					char buffer[1024];
					sprintf_s(buffer, "%.1f", ( lVal / (double)m_timeScale ));
					m_curTime = atof(buffer);
				}
			}
			else if (iType == 2) // Effect
			{
				if (m_tmpElement == NULL)
				{
					m_tmpElement = new Element();
					m_tmpElement->setPlayedTime(-1.0);
					// if we are in a GroupOfEffects set the time to the group time
					if (m_anchorElement)
					{
						if (m_curTime != -1.0)
							m_tmpElement->setTime(m_curTime);
					}
				}

				if (strcmp((const char*)attr, LIBXML_TYPE) == 0)
				{
					if (strcmp((const char*)value, LIBXML_WINDTYPE) == 0)
						m_tmpElement->setType(TYPE_FAN);
					else if (strcmp((const char*)value, LIBXML_VIBRATIONTYPE) == 0)
						m_tmpElement->setType(TYPE_VIBRATOR);
					else if (strcmp((const char*)value, LIBXML_LIGHTTYPE) == 0)
						m_tmpElement->setType(TYPE_LIGHT);
					else if (strcmp((const char*)value, LIBXML_WATERSPRAYERTYPE) == 0)
						m_tmpElement->setType(TYPE_WATERSPRAYER);
					else if (strcmp((const char*)value, LIBXML_TEMPERATURETYPE) == 0)
						m_tmpElement->setType(TYPE_AIRCONDITIONER);
					else if (strcmp((const char*)value, LIBXML_FOGTYPE) == 0)
						m_tmpElement->setType(TYPE_FOG);
					else if (strcmp((const char*)value, LIBXML_SCENTTYPE) == 0)
						m_tmpElement->setType(TYPE_PERFUMER);
					else
						m_tmpElement->setType(TYPE_NONE);
				}
				else if (strcmp((const char*)attr, LIBXML_PTS) == 0)
				{
					const char* val = (const char*)value;
					long int lVal = atol(val);
					char buffer[1024];
					sprintf_s(buffer, "%.1f", ( lVal / (double)m_timeScale ));
					m_tmpElement->setTime(atof(buffer));
				}
				else if (strcmp((const char*)attr, LIBXML_ANCHORELEMENT) == 0)
				{
				}
				else if (strcmp((const char*)attr, ATT_GEN_DURATION) == 0)
				{
					const char* val = (const char*)value;
					long int lVal = atol(val);

					char buffer[1024];
					sprintf_s(buffer, "%.1f", ( lVal / (double)m_timeScale ));
					m_tmpElement->addValue((const char*)attr, (const char*)buffer);
				}
				else if (strcmp((const char*)attr, ATT_GEN_FADE) == 0)
				{
					const char* val = (const char*)value;
					long int lVal = atol(val);

					char buffer[1024];
					sprintf_s(buffer,"%.1f", (lVal / (double)m_timeScale));
					m_tmpElement->addValue((const char*)attr, (const char*)buffer);
				}
				else {
					//const char* val = (const char*)value;
					//long int lVal = atol(val);
					if (m_tmpElement->getType() == TYPE_LIGHT && strcmp((const char*)attr, ATT_GEN_AUTOEXTRACTION) == 0)
					{
						if (strcmp((const char*)value, VISUAL) == 0 || strcmp((const char*)value, BOTH) == 0)
							m_bAutoColor = true;
					}

					m_tmpElement->addValue((const char*)attr, (const char*)value);
				}
			}
		}

		if (m_tmpElement != NULL)
		{
			m_Elements->push_back(m_tmpElement);
			m_tmpElement = NULL;
		}

    }
}

void Libxml::streamFileFromMemory(std::string file) {
    xmlTextReaderPtr reader;
    int ret;
	reader = xmlReaderForMemory(file.c_str(),file.length(),NULL,NULL,0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
        xmlFreeTextReader(reader);
        if (ret != 0) {
            fprintf(stderr, "failed to parse file from memory\n");
        }
    } else {
        fprintf(stderr, "Unable to open memory location\n");
    }
}


/**
 * streamFile:
 * @filename: the file name to parse
 *
 * Parse and print information about an XML file.
 */
void Libxml::streamFile(const char *filename) {
    xmlTextReaderPtr reader;
    int ret;

    reader = xmlReaderForFile(filename, NULL, 0);
    if (reader != NULL) {
        ret = xmlTextReaderRead(reader);
        while (ret == 1) {
            processNode(reader);
            ret = xmlTextReaderRead(reader);
        }
        xmlFreeTextReader(reader);
        if (ret != 0) {
            fprintf(stderr, "%s : failed to parse\n", filename);
        }
    } else {
        fprintf(stderr, "Unable to open %s\n", filename);
    }
}

Libxml::Libxml()
{
	m_Elements = new std::vector<Element*>();
	m_curTime = 0;
	m_timeScale = 1;
	m_anchorElement = false;
	m_tmpElement = NULL;
	m_bAutoColor = false;
}

Libxml::~Libxml()
{
	if (m_Elements != NULL)
	{
		delete m_Elements;
		m_Elements = NULL;
	}
}

bool Libxml::elementCompare(const Element* element1, const Element* element2)
{
	return element1->getTime() < element2->getTime();
}

bool Libxml::isAutoColorActivated()
{
	return m_bAutoColor;
}


std::vector<Element*> Libxml::parse(std::string file)
{
    LIBXML_TEST_VERSION

    streamFileFromMemory(file);

    xmlCleanupParser();
    xmlMemoryDump();

    std::sort(m_Elements->begin(), m_Elements->end(), elementCompare);

    return *m_Elements;
}

std::vector<Element*> Libxml::parse(const char* filename)
{
    LIBXML_TEST_VERSION

    streamFile(filename);

    xmlCleanupParser();
    xmlMemoryDump();

    std::sort(m_Elements->begin(), m_Elements->end(), elementCompare);

    return *m_Elements;
}

long Libxml::getTimeScale()
{
	return m_timeScale;
}

#endif

