#ifndef __myglTexture_h__
#define __myglTexture_h__

#include <string>
#include "datatypes.h"
#include "mygl.h"

using namespace std;

namespace OpenArena
{
	/*!
	 * \brief
	 * Write brief comment for Texture here.
	 * 
	 * Write detailed description for Texture here.
	 * 
	 * \remarks
	 * Write remarks for Texture here.
	 * 
	 * \see
	 * Separate items with the '|' character.
	 */
	class Texture
	{
	public:
		/*!
		 * \brief
		 * Write brief comment for Texture here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Texture here.
		 * 
		 * \remarks
		 * Write remarks for Texture here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		Texture();
		/*!
		 * \brief
		 * Write brief comment for ~Texture here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ~Texture here.
		 * 
		 * \remarks
		 * Write remarks for ~Texture here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		~Texture();
		/*!
		 * \brief
		 * Write brief comment for Filename here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Filename here.
		 * 
		 * \remarks
		 * Write remarks for Filename here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		string Filename();
		/*!
		 * \brief
		 * Write brief comment for ID here.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for ID here.
		 * 
		 * \remarks
		 * Write remarks for ID here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		GLuint ID();
		/*!
		 * \brief
		 * Write brief comment for Load here.
		 * 
		 * \param filename
		 * Description of parameter filename.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Load here.
		 * 
		 * \remarks
		 * Write remarks for Load here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool Load(string filename);
		/*!
		 * \brief
		 * Write brief comment for Load here.
		 * 
		 * \param filename
		 * Description of parameter filename.
		 * 
		 * \param min
		 * Description of parameter min.
		 * 
		 * \param mag
		 * Description of parameter mag.
		 * 
		 * \returns
		 * Write description of return value here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Load here.
		 * 
		 * \remarks
		 * Write remarks for Load here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool Load(string filename, GLuint min, GLuint mag);
		/*!
		 * \brief
		 * Write brief comment for Free here.
		 * 
		 * \throws <exception class>
		 * Description of criteria for throwing this exception.
		 * 
		 * Write detailed description for Free here.
		 * 
		 * \remarks
		 * Write remarks for Free here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		void Free();
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
		 * Write brief comment for operator < here.
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
		 * Write detailed description for operator < here.
		 * 
		 * \remarks
		 * Write remarks for operator < here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator<(const Texture&);
		/*!
		 * \brief
		 * Write brief comment for operator <= here.
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
		 * Write detailed description for operator <= here.
		 * 
		 * \remarks
		 * Write remarks for operator <= here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator<=(const Texture&);
		/*!
		 * \brief
		 * Write brief comment for operator == here.
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
		 * Write detailed description for operator == here.
		 * 
		 * \remarks
		 * Write remarks for operator == here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator==(const Texture&);
		/*!
		 * \brief
		 * Write brief comment for operator != here.
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
		 * Write detailed description for operator != here.
		 * 
		 * \remarks
		 * Write remarks for operator != here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator!=(const Texture&);
		/*!
		 * \brief
		 * Write brief comment for operator >= here.
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
		 * Write detailed description for operator >= here.
		 * 
		 * \remarks
		 * Write remarks for operator >= here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator>=(const Texture&);
		/*!
		 * \brief
		 * Write brief comment for operator > here.
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
		 * Write detailed description for operator > here.
		 * 
		 * \remarks
		 * Write remarks for operator > here.
		 * 
		 * \see
		 * Separate items with the '|' character.
		 */
		bool operator>(const Texture&);
	
	private:
		GLuint minFilter;
		GLuint magFilter;
		string filename;
		GLuint id;
	};
};	
#endif
