#pragma once
#include <stdio.h> 
#include <stdarg.h>

class Logger
{
public:

	class CONTEXT {
	public:
		enum eContext {
			//NOT ACTIVE = 0,
			//ACTIVE = 1,
			GRAPHIC = 0,
			INPUT_PARSER = 0,
			MAIN = 0,
			PATH_FINDING = 0,
			UTILITIES = 0,
			
		};
	};
	
	class SEVERITY {
	public:
		enum eSeverity {
			ERR = 0,
			LOG,
			DEBUG
		};
	};
	
private:
	//Increase minNumSeverity, all enum < m_oMiniLevel will be printed
	const SEVERITY::eSeverity m_oMinLevel = SEVERITY::ERR;
public:
	static Logger& GetInstance()
	{
		static Logger m_oInstance;
		return m_oInstance;
	}
	void Log(const SEVERITY::eSeverity& eSeverity, const CONTEXT::eContext& eContext, const char* msg, ...);

private:
	Logger() {};
	Logger(Logger const&);
	void operator=(Logger const&) = delete;
};

inline void Logger::Log(const SEVERITY::eSeverity& eSeverity, const CONTEXT::eContext& eContext, const char* msg, ...)
{
	if ((eSeverity <= m_oMinLevel) && eContext)
	{
		va_list vl;
		va_start(vl, msg);
		vprintf(msg, vl);
		va_end(vl);
	}	
};