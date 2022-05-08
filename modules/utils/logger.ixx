export module pc.utils.logger;

export auto init_console(void) -> void
{
#ifndef _CONSOLE
#ifdef _DEBUG
	AllocConsole();
	std::atexit([]() { FreeConsole(); });
#endif // _DEBUG
#endif // _CONSOLE
}

export auto last_error(const std::string_view _name) -> void
{
	// const auto code{ GetLastError() };
	// const auto message{ std::system_category().message(code) };
}
