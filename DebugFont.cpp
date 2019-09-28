#include "pch.h"
#include "DebugFont.h"

using namespace DirectX;
using namespace DirectX::SimpleMath;

using namespace std;

#if DEBUG_FONT_SINGLETON_TYPE == 0
DebugFont* DebugFont::m_pInstance = nullptr;
#elif DEBUG_FONT_SINGLETON_TYPE == 1
unique_ptr<DebugFont> DebugFont::m_pInstance = nullptr;
#else
DebugFont DebugFont::m_instance;
#endif
DebugFont::DebugFont()
	: m_pos(0, 0)
	, m_string(nullptr)
{
	m_string = new wchar_t[STRING_SIZE_MAX];
}
DebugFont::~DebugFont()
{
	delete[] m_string;
}
// ê∂ê¨
void DebugFont::create(ID3D11Device1* device, ID3D11DeviceContext1* context)
{
	m_spriteBatch = make_unique<SpriteBatch>(context);
	m_spriteFont = make_unique<SpriteFont>(device, L"SegoeUI_18.spritefont");
}
// ï`âÊ
void DebugFont::draw()
{
	m_spriteBatch->Begin();
	m_spriteFont->DrawString(m_spriteBatch.get(), m_string, m_pos);
	m_spriteBatch->End();
}
// ÉäÉZÉbÉg
void DebugFont::reset()
{
	m_spriteBatch.reset();
	m_spriteFont.reset();
}
// ï\é¶èÓïÒìoò^
void DebugFont::print(float posX, float posY, wchar_t const * const format, ...)
{
	m_pos.x = posX;
	m_pos.y = posY;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}
// ï\é¶èÓïÒìoò^ÅiVector2î≈Åj
void DebugFont::print(Vector2 pos, wchar_t const * const format, ...)
{
	m_pos = pos;
	va_list arg_ptr;
	va_start(arg_ptr, format);
	vswprintf(m_string, STRING_SIZE_MAX, format, arg_ptr);
	va_end(arg_ptr);
}