�}P� �  o�}?�"�Q��^�]r69�x�� G��o�*5��eF-�Z�^�,�%����4'I~�Yj������҅�1�Z�����"�7�<Í���B� ��	�����f�^�goQyL=�%W���dd.*�"���8c+d8K��l?葳�r�'�d���{�8�䵟�v)D5&��5���͆���~��zL�y0F�9���=�&p�v*�T����A��7���"D�/	�����gM�����*����gc����/�Az��+�|2�})ջ�����'r+�� eZ���So��\��-����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћlD)�E�T��X0�S���%v�XN��p�B�^��hz����k+^k4e��g|� 3(w6���kdh���f��E[`�����|�+�t�Z�5�7�:�3�Y.TM
��rF�U�-f*�pԟ�{M�\~��)�p�L1@�A6��,u�NY-d�Z�8酅��e���2�do*-�JV�����CM6RT��.I(����1�ΰݪS���y�����ݏɐ�l��X �\��J���{�e�9wjr��u.����v�ʵ��=�p�I5�C�Ki+����]?��YA�=~��d����`П�?=W9R�͏���të��V�, $s{N%Zv8�����=؄��)d�Y���ܡ>T�EXIa���b#��o鵦����b�C��~�6��<�2eАԀ)J��T�nϐ���3�0/�3�;ъR��բK�e�i��~��j��V�@�Q:C��꺶\�L�HӔ�P�_���٢Uᬀ�m'q\�t9(��P.l��u���A���egLimit(int nAxis);
	int  CheckDone(int nAxis);
	bool SetIOState(int nIONo, bool bOnOff);
	bool GetIOState(int nIONo);
	bool SetPos(int nAxis, double nPos);

private:
	int            m_nMotorIndex;	 
	JCMotorBase*   m_pMotorCtrl;

};

#endif 