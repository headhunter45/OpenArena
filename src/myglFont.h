#ifndef __glPrint_h__
#define __glPrint_h__

#include "mygl.h"

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Font here.
	 * 
	 * Write detailed description for Font here.
	 * 
	 * \remarks
	 * Write remarks for Font here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Font
	{
	private:
		short screenWidth;
		short screenHeight;
		unsigned int base;
		GLuint texture;
		bool status;
	
	public:
		/*!
		 * \brief
		 * Write brief comment for Font here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Font here.
		 * 
		 * \remarks
		 * Write remarks for Font here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Font();
		/*!
		 * \brief
		 * Write brief comment for ~Font here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Font here.
		 * 
		 * \remarks
		 * Write remarks for ~Font here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		~Font();
		/*!
		 * \brief
		 * Write brief comment for BuildFont here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for BuildFont here.
		 * 
		 * \remarks
		 * Write remarks for BuildFont here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool BuildFont(const char*);
		/*!
		 * \brief
		 * Write brief comment for FreeFont here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for FreeFont here.
		 * 
		 * \remarks
		 * Write remarks for FreeFont here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool FreeFont();
		/*!
		 * \brief
		 * Write brief comment for Print here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Print here.
		 * 
		 * \remarks
		 * Write remarks for Print here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Print(int, int, const char*, unsigned int = 0);
		/*!
		 * \brief
		 * Write brief comment for Loaded here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Loaded here.
		 * 
		 * \remarks
		 * Write remarks for Loaded here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool Loaded();
		/*!
		 * \brief
		 * Write brief comment for SetScreenDimensions here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetScreenDimensions here.
		 * 
		 * \remarks
		 * Write remarks for SetScreenDimensions here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetScreenDimensions(short, short);
		/*!
		 * \brief
		 * Write brief comment for SetScreenWidth here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetScreenWidth here.
		 * 
		 * \remarks
		 * Write remarks for SetScreenWidth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetScreenWidth(short);
		/*!
		 * \brief
		 * Write brief comment for SetScreenHeight here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetScreenHeight here.
		 * 
		 * \remarks
		 * Write remarks for SetScreenHeight here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetScreenHeight(short);
		/*!
		 * \brief
		 * Write brief comment for ScreenWidth here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ScreenWidth here.
		 * 
		 * \remarks
		 * Write remarks for ScreenWidth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		short ScreenWidth();
		/*!
		 * \brief
		 * Write brief comment for ScreenHeight here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ScreenHeight here.
		 * 
		 * \remarks
		 * Write remarks for ScreenHeight here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		short ScreenHeight();
	};
};
#endif
