�}p� o  ��NaV��Q��-^�s9�֏�W����EI�'�o�u�6�}O��w�ɢ��ܧ��4���L�������tS/w����E����.�C�D�`�rS�=�wL=4���k��Cu!�/_6w���M��d)Lpr�%�U���
1lrr~�I�"d�sa��?*�,D6_UR�p-�T! ��#h˷�2ڒ���_mw&M����E�L+�-�������k��ܨh����8Q�c�yz�h�:��]�E3ch����+�y�!+Y��!#��=A�I�R,f���:�~V^0��%�:�^�gm���O�F�3�>X񚋞+]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћl�0��ׄ?0o��}'��Ŝ�mF��-h��������0U.��A(�A�d��P7y�C�Pe�g6w�'��jE��$$�90M�Uٻ������㣟e�h�J.��(��RA�� �Jq�(���}�p�sw<4������ �D���q� ����h<3�$��oH �o��Kz�[�p�ŵ�nk������gč�g�,΂��X�+������%�ڳ�U���+�"{�b�1;���v33A~��\?���ث�s�@,��3y�圿X��L䀲qc�^͇�Bd���C�#�
4w�[�J-X��lҴ�F���]�P���V�$zc�50����,�Z����M�T��:����I�jmWb���9��xǕ#��=c���Q���A�-t>c+n9̏E�_,c �%Ep�,��w��h�˕����>*��gt�����-~�x��:L1�o8�L�OG`n!|&`����%\�p��~G���`���-�hannelIndex, eInfo, "recv serial command:" + strRecvCmd);
	if (NULL != strstr(strRecvCmd.c_str(), Ok0().c_str()))
	{
		if (strSendCmd == Measurement())
		{
			int nIndex = strRecvCmd.find(' ');
			strRecvCmd = strRecvCmd.substr(nIndex + 1);
			if (-1 != strRecvCmd.find_last_of('\r'))
			{
				strRecvCmd = strRecvCmd.substr(0, strRecvCmd.length() - 1);
			}
			strList = GlobarFunction::SplitString(strRecvCmd, ';');
		}
		return true;
	}
	return false;
}






