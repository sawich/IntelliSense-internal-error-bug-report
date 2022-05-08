export module pc.natives.window;

import pc.utils.logger;
import pc.utils.window.register_class;
import pc.natives.window_handle;
import pc.utils.convert;

export struct window final : public window_handle
{
public:
	inline constexpr static auto default_width{ CW_USEDEFAULT };
	inline constexpr static auto default_height{ CW_USEDEFAULT };

public:
	template<typename TCallback, typename ...TArgs>
	[[nodiscard]]
	constexpr auto loop(TCallback&& _callback, TArgs&&... _args) const->int32_t
	{
		MSG msg{};
		while (true) {
			while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
				if (msg.message == WM_QUIT) { return EXIT_SUCCESS; }

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			_callback(std::forward<TArgs>(_args)...);
		}

		return lodword(msg.wParam);
	}

	inline auto show(void) const noexcept -> void { ShowWindow(m_handle, SW_SHOW); }
	inline auto hide(void) const noexcept -> void { ShowWindow(m_handle, SW_HIDE); }

	constexpr window(void) noexcept {}

	window(const std::u16string_view _name, const size_t _width, const size_t _height)
	{
		const DWORD style{ WS_OVERLAPPEDWINDOW };

		RECT rect{ .right = LOWORD(_width), .bottom = LOWORD(_height) };
		if (FALSE == AdjustWindowRect(&rect, style, false)) {
			last_error("AdjustWindowRect");
			std::exit(EXIT_FAILURE);
		}

		const HINSTANCE instance{ GetModuleHandle(NULL) };
		const auto name{ reinterpret_cast<LPCTSTR>(_name.data()) };

		const auto x_pos{ CW_USEDEFAULT };
		const auto y_pos{ CW_USEDEFAULT };

		const auto width{ rect.right - rect.left };
		const auto height{ rect.bottom - rect.top };

		m_handle = CreateWindow(name, name, style, x_pos, y_pos, width, height, NULL, NULL, instance, NULL);

		if (not m_handle) {
			last_error("CreateWindow");
			std::exit(EXIT_FAILURE);
		}
	}

	constexpr window(const window& _window) = delete;
};
