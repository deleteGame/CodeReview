�}�� �  ~�Ndj��Q��^�]r69�x�� G��o�*5��eF-�Z�^r<�%����4'I~�Yj��������70����/�x�y�oR��M�u�'�Mn^k<�`�F4B��✏( ���H<�QȠ�pW��~���jO_�َ�F��1z�4�����?�RQ��f�9���T��8}Ʈ3D�Ȋ��o�>���� ���X���@%ǨU;��P�ķ�����p����%G5)��15,)��B[q@.�B48]'^�a�n\��*1�]�yK����1��:�w���	��So��\��-����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћlD'�G��]�/��S�����\\m�Y�U�Үט���ߢ�Q�x��DLKc��/��V;X�M��(،&Y����@ڶR[�r[��ܐ$4@t�s���9oʦ�y��;��?Ѧ9/������b!{j�r�kL�F��"3��x�>z��)f��[3��,>P��33�QJ�����#-����Z<ʓ�a��������Ɵ�����
�cڋ&��9���(�,����օ)F�%G�,˘�*�k�4��T�:X;�E~�e��k�2��vu���͜�so>�k��@�E�h�$.�2�Z%�[����������U���l���C^x�Y�cץ�/���J�>��m<wV����
d"�����d�.��:X*ė�y���S�w6�U#SI��~�V��r�FV�Fٝ�pW��)����������u���*�ڊ�oA��L� 2TM�!��	_�ط��9e:V�^:7	��9!��RZ�qO�tڬ��y(�	��JE�8W���%��}R��D��ol EMGStop(int nAxis)=0;
	virtual bool GetCurPos(int nAxis, long& nPos)=0;
	virtual bool SetPos(int nAxis, double nPos)=0;

	virtual bool SetIOState(int nIONo, bool bOnOff)=0;
	virtual bool GetIOState(int nIONo) = 0;

	virtual bool GetConnect() { return false; }

};



#endif