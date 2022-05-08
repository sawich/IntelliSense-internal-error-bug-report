export module pc.natives.window_handle;

import pc.utils.logger;

export struct window_handle
{
	constexpr operator HWND(void) const noexcept { return m_handle; }

	constexpr window_handle(void) noexcept {}
	constexpr window_handle(HWND&& _handle) noexcept : m_handle{ _handle } {}

	~window_handle(void) noexcept
	{
		if (not DestroyWindow(m_handle)) {
			last_error("DestroyWindow");
		}
	}

protected:
	HWND m_handle{ NULL };
};
