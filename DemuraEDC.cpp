�}�� �  ��R�T�Q��^�s%�
oҌ�����)���K���*_��mr��k"�f)�]�O�}�+$�b
f�E-�-*h4E�	��$2�[u���(�Ќ��7ƫ�	p���3�����s
2�2Bz;?��X��}N�?����(R��⯻5�X��a!�S$
L�>�0�:���H}���^?['�΂Gд�O*p��Μys�Y���j-ZLy����qx�Fa���}.	ßmg�&���d�k�Cil�՜5Q�/d����XT�X2�V�����/��g"+=�So��\��-����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћlD,�~jF�T�.��|�����\1�0�B�d+!\sW���K�0ݰ_����W!e@���H�����i��%��Dj9Vx�i����GHR����&�y\/CU�^�p�No��	�%�GO��bv��U��"�V~�!�\n���5�I����Gǝ��ΰ�s�O��Kg�wZL)}���^*x�1B��͜����i⺕G��c�/ӛ��I�%VL'�S�-S��:�F����iWԩ���u0iuK�:���CN�%#�C*���z;�/�
�M��䭋������v�$��Ȃ�qE�2��b��Kͱ�C7�E�BvA��bK����'��w���d�I���}�$�LC���ԗ�����c�%i�ǩꓱ���wkS4J����e1��c��>�!$�B��ov�	�t޵��Sp�^7�]����L0RU���;Nk�5\�����^ݒ��@;�ٍ��B�J�CA[b	�v1����]��q�L6e���N�vW��"��3���'	tion)
	{
		m_pEDCAction = new QAction("EDC");
	}
	connect(m_pQuitAction, SIGNAL(triggered(bool)), qApp, SLOT(quit()));
	connect(m_pEDCAction, SIGNAL(triggered(bool)), this, SLOT(Slot_ShowEDC()));
	m_pMenu = new QMenu(this);
	m_pMenu->addAction(m_pEDCAction);
	m_pMenu->addAction(m_pQuitAction);	
	m_pSystemTrayIcon->setContextMenu(m_pMenu);
	m_pSystemTrayIcon->show();
}

void DemuraEDC::Slot_CloseWindow()
{
	this->close();
}

void DemuraEDC::Slot_ShowEDC()
{
	m_pJcEDCForm->show();
}
