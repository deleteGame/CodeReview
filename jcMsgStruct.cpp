�}�� �  
e�q�Q��� ^�rU�KҌ0e���B!�U��g;RӞ�U��x^��Z����$��;���5Ӷ"���`����Fڞfi'Q���:tNH���%jΔ��Q�\?ݪ����
h^)�����x�q�W������D��T�'��g�0�����@�͏�n2�*��%�Ǻ�>��U�fjHRK��D��P|8&1:����$�B���4��r
�@$q�W<��Ǚ5� ���eH�]��&.������6T�X�w<bJ������ͽ.-�e1)ջ�����'r+�� eZ���So��\��-����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћl�:g<�ߢ��;H۹�*˟������u]�D
k�P���3?p���h�3�,�GZ�N=�����C6��zG3m��m�yw�.�Ji壌x�� �S�s�G�}��If(�M� ;+[���Scp(�&�UN�Y[�k��$!\d»	���n�6��?�u�"��ʦ�C|��_�m��X0�`�r���`�"oy���J��RnE&d��5�V�@a��X	!��B�#v�(3�覘t;�U���ڋ3H_(R������&����cq�+1^G��������Y>b�`����A�ϴ���E�D:L���H�o����h"�3��O�^ֈ��j˧v�fe�*}G,q�d�P�`�0ҙQ�d�+����˙��L�6T7��e��_�l<8y��$B����q�g|�n��#��n���();�K���	?MLWšvX]��K�e	��3捂��P�9;�8̓�dW��Ʀ��I`7ϖ(% ��:d����s������EJ���9jL{�i�ol�*����e�}w.M<{3~�Wދ�Z�Ƥ����Ҝh!�|���&+�Y�/&�.?Yq����#���Eȵ��+Y�DT4��CD������ �w�:�R7�M��+f�\i� ��,���)Ɛ���#V&�4�؏���_�X�E�-�U��\[8�'�h��V'�$: ��W ��]�!����Y,���8
&}���Hￃq�: �nA�l���mq_������)�SsaR�^y����U��Bo��O珇 }��s�����6�#V8$����}_ꜘ)4)j���:(�\��b$W2&Kk.V�5l�%ps�M���/��"�;��t�,�hU,�i|l�I� +���կ�G28>��F�:B.k���LR:������������伨c�ꃏm��ϕ�|%H9N@u����k�Q�E2";��`fK���$y4睍F��`�=M���?jrh���\f��GICB&YJ������&ê>9[$X2��z� �Z���d����Q
}

bool JcDemuraMessage::ExistBaseData()
{
	bool bExist = false;
	if (NULL == m_pDemuraBaseData)
	{
		return true;
	}
	gQtMutex.lock();
	auto iter = gJcDemuraMessageDataMap.find(m_pDemuraBaseData);
	if (iter != gJcDemuraMessageDataMap.end())
	{
		if (m_pDemuraBaseData->GetDeleteIndex() >= 1)
		{
			bExist = true;
		}
	}
	gQtMutex.unlock();
	return bExist;
}