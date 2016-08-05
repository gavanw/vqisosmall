// f00305_shader.h
//

#include "f00305_shader.e"
#define LZZ_INLINE inline
Shader::Shader (Singleton * _singleton)
                                      {
		singleton = _singleton;
		curUBIndex = 0;
	}
char * Shader::textFileRead (char const * fileName)
                                                        {
		
		char* text = "";
		bool failed = true;
	    
		if (fileName != NULL) {
	        FILE *file = fopen(fileName, "rt");
	        
			if (file != NULL) {
	            fseek(file, 0, SEEK_END);
	            int count = ftell(file);
	            rewind(file);
	            
				if (count > 0) {
					text = new char[(count + 1)];
					//(char*)malloc(sizeof(char) * (count + 1));
					count = fread(text, sizeof(char), count, file);
					text[count] = '\0';
					failed = false;
				}
				fclose(file);
			}
		}

		if (failed) {
			doTraceND("FAILED TO READ FILE: ", fileName);
		}
		else {
			//doTrace("READ FILE: ", fileName);
		}
		
		
		return text;
	}
void Shader::validateShader (GLuint shader, char const * file)
                                                                        {
		//pushTrace("validateShader(", file, ")");
		
		const unsigned int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		GLsizei length = 0;
	    
		glGetShaderInfoLog(shader, BUFFER_SIZE, &length, buffer);
		if (length > 0) {
			doTraceND("Shader " , i__s(shader) , " (" , (file?file:"") , ") compile error: " , buffer);
			LAST_COMPILE_ERROR = true;
		}
		//popTrace();


	}
int Shader::validateProgram (GLuint program)
                                                   {
		//pushTrace("validateProgram()");
		
		const unsigned int BUFFER_SIZE = 512;
		char buffer[BUFFER_SIZE];
		memset(buffer, 0, BUFFER_SIZE);
		GLsizei length = 0;
	    
		memset(buffer, 0, BUFFER_SIZE);
		glGetProgramInfoLog(program, BUFFER_SIZE, &length, buffer);
		if (length > 0) {
			doTraceND( "Program " , i__s(program) , " link error: " , buffer);
			LAST_COMPILE_ERROR = true;
			//popTrace();
			return 0;
		}
	    
		glValidateProgram(program);
		GLint status;
		glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
		if (status == GL_FALSE) {
			doTraceND( "Error validating shader " , i__s(program));
			LAST_COMPILE_ERROR = true;
			//popTrace();
			return 0;
		}
		
		//popTrace();
		return 1;
		
	}
int Shader::countOc (string * src, string testStr)
                                                 {
		int totCount = 0;
		int bInd = 0;
		bool dc = true;
		int fnd = 0;
		
		while (dc) {
			fnd = src->find(testStr, bInd);
			if (fnd != std::string::npos) {
				bInd = fnd+1;
				dc = true;
				totCount++;
			}
			else {
				dc = false;
			}
		}
		
		return totCount;
	}
void Shader::init (string _shaderFile, bool doBake)
                                                   {
		
		
		
		const char* shaderFile = _shaderFile.c_str();
		
		uniVec.clear();
		paramVec.clear();
		paramMapTemp.clear();
		
		shader_vp = glCreateShader(GL_VERTEX_SHADER);
		shader_fp = glCreateShader(GL_FRAGMENT_SHADER);
	    
	    
		std::size_t found;
		std::size_t found2;
		std::size_t found3;

		int baseIndex;
		int uniCount = 0;
		int dolCount = 0;
		
		
		vector<string> allTextStringSplit;

		bool doCont;
		
		string paramName;

		int i;

		const char* allText = textFileRead(shaderFile);


		if (allText == NULL) {
			doTraceND( "Error: Either vertex shader or fragment shader file not found." );
			LAST_COMPILE_ERROR = true;
		}
		else {
			
				string allTextString(allText);
				
				
				

				//
				
				dolCount = countOc(&allTextString,"$");

				if (dolCount == 2) {
					
					uniCount = countOc(&allTextString,"ublock");


					baseIndex = 0;
					doCont = true;
					while (doCont) {
						found = allTextString.find('@', baseIndex);
						if (found != std::string::npos) {
							
							
							baseIndex = found+1;
							allTextString[found] = ' ';
							
							found3 = allTextString.find(' ', baseIndex);
							found2 = allTextString.find('@', baseIndex);
							
							if (found2 != std::string::npos) {
								
								if ( 
									((found2-found) > 32) || // max var length of 32
									(found3 < found2) // found a space between the delimitters
								) { 
									//baseIndex = found+1; // already set
								}
								else {
									baseIndex = found2+1;
									allTextString[found2] = ' ';
									
									paramName = allTextString.substr(found + 1, (found2-found)-1);
									
									if (paramMapTemp.find( paramName ) == paramMapTemp.end()) {
										paramMapTemp[paramName] = 0.0f;
										paramVec.push_back(paramName);
										
										if (paramMap.find( paramName ) == paramMap.end()) {
											paramMap[paramName] = 0.0f;
										}
										
										//cout << "paramName --" << paramName << "--\n";
										
									}
								}
								
								
								
								doCont = true;
							}
							else {
								doCont = false;
							}
							
							
						}
						else {
							doCont = false;
						}
					}
					
					
					
					allTextStringSplit = split(allTextString, '$');
					
					allTextStringSplit[0].append("\n");
					
					if (doBake) {
						for (i = 0; i < paramVec.size(); i++) {
							allTextStringSplit[0].append("const float ");
							allTextStringSplit[0].append(paramVec[i]);
							allTextStringSplit[0].append("=");
							allTextStringSplit[0].append(f__s(paramMap[paramVec[i]]));
							allTextStringSplit[0].append(";\n");
						}
					}
					else {
						for (i = 0; i < paramVec.size(); i++) {
							allTextStringSplit[0].append("uniform float ");
							allTextStringSplit[0].append(paramVec[i]);
							allTextStringSplit[0].append(";\n");
						}
					}
					
					

					string vertStr = allTextStringSplit[0] + allTextStringSplit[1];
					string fragStr = allTextStringSplit[0] + allTextStringSplit[2];

					const GLchar* vertCS = new char[vertStr.length() + 1];
					const GLchar* fragCS = new char[fragStr.length() + 1];

					std::strcpy((GLchar*)vertCS,vertStr.c_str());
					std::strcpy((GLchar*)fragCS,fragStr.c_str());


			    	glShaderSource(shader_vp, 1, &(vertCS), 0);
					glShaderSource(shader_fp, 1, &(fragCS), 0);
				    
					glCompileShader(shader_vp);
					validateShader(shader_vp, shaderFile);
					glCompileShader(shader_fp);
					validateShader(shader_fp, shaderFile);



					shader_id = glCreateProgram();
					glAttachShader(shader_id, shader_fp);
					glAttachShader(shader_id, shader_vp);
					glLinkProgram(shader_id);
					validateProgram(shader_id);

					delete [] vertCS;
					delete [] fragCS;


					for (i = 0; i < uniCount; i++) {
						uniVec.push_back(UniformBuffer());
						uniVec.back().init(shader_id, i);
					}


				}
				else {
					LAST_COMPILE_ERROR = true;
					doTraceND( "Error: " , shaderFile , "does not contain proper amount of splits ($)\n" );
				}
				
				
				delete[] allText;
			  
		}
		
		
		//popTrace();
		
	}
Shader::~ Shader ()
                  {

		uniVec.clear();

		//pushTrace("~Shader()");
		glDetachShader(shader_id, shader_fp);
		glDetachShader(shader_id, shader_vp);
		glDeleteShader(shader_fp);
		glDeleteShader(shader_vp);
		glDeleteProgram(shader_id);
		//popTrace();
	}
unsigned int Shader::id ()
                          {
		//pushTrace("id()");
		return shader_id;
		//popTrace();
	}
void Shader::bind ()
                    {
		//pushTrace("bind()");
		glUseProgram(shader_id);
		//popTrace();
	}
void Shader::updateUniformBlock (int ubIndex, int ubDataSize)
                                                             {
		uniVec[ubIndex].updateUniformBlock(ubDataSize);
	}
void Shader::invalidateUniformBlock (int ubIndex)
                                                 {
		uniVec[ubIndex].invalidateUniformBlock();
	}
void Shader::beginUniformBlock (int ubIndex)
                                            {
		curUBIndex = ubIndex;
		uniVec[ubIndex].beginUniformBlock();
	}
bool Shader::wasUpdatedUniformBlock (int ubIndex)
                                                 {

		if (uniVec.size() > ubIndex) {
			return uniVec[ubIndex].wasUpdatedUniformBlock();
		}
		else {
			return true;
		}

		
	}
void Shader::unbind ()
                      {
		//pushTrace("unbind()");
		glUseProgram(0);
		//popTrace();
	}
void Shader::setTexture (GLchar const * name, int texUnit, int texId)
                                                                    {
		GLint baseImageLoc = glGetUniformLocation(shader_id, name);

		glUniform1i(baseImageLoc, texUnit); //Texture unit 0 is for base images.
		
		//When rendering an objectwith this program.
		glActiveTexture(GL_TEXTURE0 + texUnit);
		glBindTexture(GL_TEXTURE_2D, texId);
	}
void Shader::setVec (GLchar const * name, GLfloat const * vecData, int vecSize)
                                                                             {
		
		GLint loc = glGetUniformLocation(shader_id, name);
		
		switch (vecSize) {
			case 0:
				doTraceND( "Error: vecSize of 0 in setVec" );
			break;
			case 1:
				glUniform1fv(loc, 1, vecData);
			break;
			case 2:
				glUniform2fv(loc, 1, vecData);
			break;
			case 3:
				glUniform3fv(loc, 1, vecData);
			break;
			case 4:
				glUniform4fv(loc, 1, vecData);
			break;
		}
	}
void Shader::setVecString (string name, GLfloat const * vecData, int vecSize)
                                                                            {
		
		GLint loc = glGetUniformLocation(shader_id, name.c_str());
		
		switch (vecSize) {
			case 0:
				doTraceND( "Error: vecSize of 0 in setVec" );
			break;
			case 1:
				glUniform1fv(loc, 1, vecData);
			break;
			case 2:
				glUniform2fv(loc, 1, vecData);
			break;
			case 3:
				glUniform3fv(loc, 1, vecData);
			break;
			case 4:
				glUniform4fv(loc, 1, vecData);
			break;
		}
	}
void Shader::setShaderArrayfVec4 (string paramName, float * x, int count)
                                                                        {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform4fv(loc, count, x);
	}
void Shader::setShaderArrayfVec3 (string paramName, float * x, int count)
                                                                        {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform3fv(loc, count, x);
	}
void Shader::setShaderArray (string paramName, float * x, int count)
                                                                   {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform1fv(loc, count, x);
	}
void Shader::setShaderFloat (string paramName, float x)
                                                       {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform1f(loc,x);
	}
void Shader::setShaderVec2 (string paramName, float x, float y)
                                                               {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform2f(loc,x,y);
	}
void Shader::setShaderVec3 (string paramName, float x, float y, float z)
                                                                        {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform3f(loc,x,y,z);
	}
void Shader::setShaderVec4 (string paramName, float x, float y, float z, float w)
                                                                                 {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform4f(loc,x,y,z,w);
	}
void Shader::setShaderInt (string paramName, int x)
                                                   {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform1i(loc,x);
	}
void Shader::setShaderfVec2 (string paramName, FIVector4 * f)
                                                            {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform2f(loc,f->getFX(),f->getFY());
	}
void Shader::setShaderfVec3 (string paramName, FIVector4 * f)
                                                            {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform3f(loc,f->getFX(),f->getFY(),f->getFZ());
	}
void Shader::setShaderfVec4 (string paramName, FIVector4 * f)
                                                            {
		GLint loc = glGetUniformLocation(shader_id, paramName.c_str());
		glUniform4f(loc,f->getFX(),f->getFY(),f->getFZ(),f->getFW());
	}
void Shader::setShaderFloatUB (string paramName, float x)
                                                         {
		int cp = uniVec[curUBIndex].uniPosition;

		uniVec[curUBIndex].uniData[cp] = x;
		uniVec[curUBIndex].uniPosition += 1;
	}
void Shader::setShaderfVec4UB (string paramName, FIVector4 * f)
                                                              {

		int cp = uniVec[curUBIndex].uniPosition;

		uniVec[curUBIndex].uniData[cp+0] = f->getFX();
		uniVec[curUBIndex].uniData[cp+1] = f->getFY();
		uniVec[curUBIndex].uniData[cp+2] = f->getFZ();
		uniVec[curUBIndex].uniData[cp+3] = f->getFW();
		uniVec[curUBIndex].uniPosition += 4;
	}
#undef LZZ_INLINE
 
