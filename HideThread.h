�}]� �  ��ҩ�13�Q��� ^�r��K֏�Q��6�ZL���"5�ڲ�t�9�֟B}
N!����̽;�ﻻÈt��N���j��yk�
�~�3���s�{�Y���\�_�M�	��%mɼ}.�8��od�gv��`���p�����J)�h]�����1��3��t�[󵦍C5>b
y����7�%bZ�__N�r0�<�f5���[�Tp +#7�}���0��-��!�G��#6r,�g�ΡPN�?.�5�r���9�m�.-�e1)ջ�����'r+�� eZ���So��\��-����a_:�]軠μ��f߆d�ՃY��� :�.�jl��:�TK�FY�{,>٣�'�p�@�L��#�:*
)��ɀdR��p<@�g�K��n��c�QܛVs�/],XX��D�}_��ê���'�s�G8�Z.��:�.s�}�1%����5͗k��d�����n(����"�^p߶ћig();

Q_SIGNALS:
	void Signal_CloseWindow();

private:
	QWidget* m_pParent;
	bool     m_bStop;
	QString m_strPatternDir;
	int m_nPatternBit;
	QDateTime m_tLastModifeTime;
	QVector<QString> m_tPatternPathVec;	
};

#endif // QPATTERNTHREAD_H
