#ifndef __screen_h__
#define __screen_h__
#include <string>

#if defined HAVE_CONFIG_H
#include "config.h"
#endif

using namespace std;
namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Screen here.
	 * 
	 * Write detailed description for Screen here.
	 * 
	 * \remarks
	 * Write remarks for Screen here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Screen
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for Screen here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Screen here.
		 * 
		 * \remarks
		 * Write remarks for Screen here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Screen();
		/*!
		 * \brief
		 * Write brief comment for GetWidth here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetWidth here.
		 * 
		 * \remarks
		 * Write remarks for GetWidth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		int GetWidth();
		/*!
		 * \brief
		 * Write brief comment for GetHeight here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetHeight here.
		 * 
		 * \remarks
		 * Write remarks for GetHeight here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		int GetHeight();
		/*!
		 * \brief
		 * Write brief comment for GetColorDepth here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetColorDepth here.
		 * 
		 * \remarks
		 * Write remarks for GetColorDepth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		int GetColorDepth();
		/*!
		 * \brief
		 * Write brief comment for GetFullscreen here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetFullscreen here.
		 * 
		 * \remarks
		 * Write remarks for GetFullscreen here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool GetFullscreen();
		/*!
		 * \brief
		 * Write brief comment for GetName here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for GetName here.
		 * 
		 * \remarks
		 * Write remarks for GetName here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		const char* GetName();
		/*!
		 * \brief
		 * Write brief comment for SetWidth here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetWidth here.
		 * 
		 * \remarks
		 * Write remarks for SetWidth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetWidth(int);
		/*!
		 * \brief
		 * Write brief comment for SetHeight here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetHeight here.
		 * 
		 * \remarks
		 * Write remarks for SetHeight here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetHeight(int);
		/*!
		 * \brief
		 * Write brief comment for Resize here.
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
		 * Write detailed description for Resize here.
		 * 
		 * \remarks
		 * Write remarks for Resize here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Resize(int, int);
		/*!
		 * \brief
		 * Write brief comment for SetColorDepth here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetColorDepth here.
		 * 
		 * \remarks
		 * Write remarks for SetColorDepth here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetColorDepth(int);
		/*!
		 * \brief
		 * Write brief comment for SetFullscreen here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetFullscreen here.
		 * 
		 * \remarks
		 * Write remarks for SetFullscreen here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetFullscreen(bool);
		/*!
		 * \brief
		 * Write brief comment for ToggleFullscreen here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ToggleFullscreen here.
		 * 
		 * \remarks
		 * Write remarks for ToggleFullscreen here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void ToggleFullscreen();
		/*!
		 * \brief
		 * Write brief comment for SetName here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetName here.
		 * 
		 * \remarks
		 * Write remarks for SetName here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetName(const char*);
		/*!
		 * \brief
		 * Write brief comment for SetName here.
		 * 
		 * \param 
		 * Description of parameter .
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for SetName here.
		 * 
		 * \remarks
		 * Write remarks for SetName here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void SetName(string);
	protected:
		short _width;
		short _height;
		char _colorDepth;
		bool _fullscreen;
//	public:
		string _name;
	};
};
#endif
