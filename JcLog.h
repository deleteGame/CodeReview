�}�� z  2�R�C��Q��$^
5��h�[o-K3FZX�|��ڵZ:�)
�ߡb��:��9S��)J�9h��/"����<V/.b�}7:N��x�l���-6��i}	�nH����}p�U��\!��D~f�B!�z��Y��\c��nld��D�L� .�k�
I��2�_H��ߢ&˔�y�vC�u5�$�ꝭ��� ]JU{�kI��q@�4.hx�Ԉ��P�3�}�l��@��>f�4���L��;��h�SU�eh�$���1z�vzЖZ�N�*��ȝ�n�8���Ql�Z�i�|����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћlD)�E�*/{"�sR�75���!�IL'feK��d�ת�����>�����r�1T��[��iQ��t�	��s˒�H3��G��$��&�1@�B�wyni���AdqE&ܜ{�Vpˍa�n���/D^��-���K'"B+�J��s%�O���i�h�o*-�J/��#���a{z-��sB*����vQ��ǿ�r�μcP���/��ԇ޴�qm�^��}�:��zK���|�	�0+#rښwOӫ��/a�]����hF��H.��KvJ��̔?��<SE�tu��d����a���q:+V���ޡ�_�����7KOjDc[u��1������Q�!r��E�Ē�U	�~RQ@���ylϳL򹯐���i�O�h�e��_�Tuވ��(m��\�:��  �Ě<�54u�|^2�2��R��բK�e�i��~��j��V�@�Q:C��꺶\�L�HӔ�P�_���٢Uᬀ�m'q\�t9(��P.l��u���A���;
	void WriteLogFormat(int nModeType, int nClientIndex, int nInformationType, char* outputString, ...);	
	void WriteMsgIdLog(int nModeType, int nClientIndex, int nDirection, int nMessageId);
	void SetLogFileType(int nLogFileType);
private:
	string m_strCurrentDirPath;	
	char m_OutputBuff[OUTPUT_MAX_BUFFLEN];	
	char m_SpritfOutputBuff[OUTPUT_MAX_BUFFLEN];	
	CRITICAL_SECTION	m_tLogCS;
	map<int, LOGDataT> m_tLogMap;	
	int  m_nLogFileType;
private:
	void CloseLogFile();
};
#endif // _JCLOG_H_
