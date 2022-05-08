export module pc.utils.window.register_class;

import pc.utils.logger;

export auto register_class(const HINSTANCE _instance, const std::u16string_view _name) -> void
{
	const WNDCLASSEXW wcex{
		.cbSize = sizeof(WNDCLASSEX),
		.style = CS_HREDRAW | CS_VREDRAW,
		.hInstance = _instance,
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.lpszClassName = reinterpret_cast<LPCTSTR>(_name.data()),
	};

	if (FALSE == RegisterClassEx(&wcex)) {
		last_error("RegisterClassEx");
		std::exit(EXIT_FAILURE);
	}
}
