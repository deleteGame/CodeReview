�}z� �  ����|Q�� ^�r��K�L�J��r�ja��E��!u�%~����[�\�� ������c�(PG ~C���=�r�
(`6�b>L�=P��jdVn�M�����s���g/�����VWb��I�_�Ã���{3�9y��Cv�A���M�P7$���#�3}��P(�T;q������/�}�1z����a�̜�oS3=}�&�w�p!���>;�S^���z$�Z�@?�Hk�?�b�{l5l'�;'8�M�ǬQ�'����o������E�Q�-nk��#�-����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћl*|=$����Jw����%wf�8��r�P\�N��iA���;�}	�xO�E�ʉb�X��R�u���2�Xs�hU�}�~Jǚ�8=��+�X�,��������Ȭ�t�:��l]�%Se���_#�d�!�p�S��9r���?|���͏a�S��a�{kfo��|B�H^��53�R7I��n�]I���6�S�B�ZRG[tV)��/*$G*[�����rx��^޲"�*�Q�@r����NDj14v��;k����7|�m�CcnZ��m&�ԥ=]q(��;LE��#�|� �#Ʊ�(�R�?��+�y㭏Q8�����E��f��g�9�'o�7���Ȳ����S#�I��+)�OO��H\{�~`��t� [�[e0o�E�]�M�;T�2�S
��6\�|��>�ޖ8uIjs����;:^띴D��byӇ�9�\�,�!m����<����r(�7�EW q��+�g1UX�e���w�������=�����lD+�]G|tZ���"����`�B��/!��ˆ�]E��u��_g<�i�Q��S��Wz�-�����̶�;�;+���G�8jpG���&O^��|��|��+�HG�U�X�b�݅	��v�s���Ð/X�\X����R �޲�O�s�yi�T8bs���3��&a��Sd�[?�R������RH��,����c��J������AC��(7#�ν� ��mIo�%�;�fe}�{%2m���.�l��XY�c�?+��bc��p�B`����!.�LR���pe��V�bU�a�5��UǸf>  tɝ^�С�@�(��R�*�#@�m>���'�b�$yOP�-�&u�r��"�C`���	U��/ބd��d�FA ���_��U4�H�� �����3
�̆��sv`p�cu�ӇǕfH����V)޺���C��3�E��l3�**+(�k�~�6������^�h� .j�Ȣ���	k�l!s�����$&�l�&^�Y�Է����4l�$~��%]T��kR�����#���qO�4���C���Bl��P?�g���i�?�����7_K���eN�OU�d�\����F�-@��܀���<�*�9:���B�$N]I���O܂��v�*A���pdJ��[��J�Sb1$��hǑr~>qj���S�8P��b��(��4��+�Th8�w��'��,���V��WrR@F�1�Ml*�-'*qT��T�4�'����,�\�3�50%�Vx���I�h�OLSq��6�?�� ���ێ%�g{�j��{�&S�ag��:x#���
1t�2�@�S��ur4iY'#a{Rw۟�`X��٧X���*˩R��V��9��^qI�92im{]���Ja��ѐf�?&\9��i��(!H��L���B�]�Ū}��U��3�bv+h�M#�����в�Pqj�E#�RB��	xr��j�<��#��>[�ɼ�/g���#x�4}�F����0�w��$��d;
	bool					CheckSocketConn(bool bwait=true);

private:
	CEvent					m_WaiteRecvEvent;
	SOCKET*					m_Socket;
	CRITICAL_SECTION		m_csSendSync;
	CRITICAL_SECTION		m_csRecvSync;
	CString					m_sendbuf;
	CVATCommSettings*		m_pSettings;
	CVATCommChannel*		m_pVATCommChannel;
	bool					m_bsended;
	int						m_nTryConnTime;
public:
	char*					m_RecvMsg;
};


#endif