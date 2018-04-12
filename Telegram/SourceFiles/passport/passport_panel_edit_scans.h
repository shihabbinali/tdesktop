/*
This file is part of Telegram Desktop,
the official desktop application for the Telegram messaging service.

For license and copyright information please follow this link:
https://github.com/telegramdesktop/tdesktop/blob/master/LEGAL
*/
#pragma once

#include "ui/rp_widget.h"

class BoxContentDivider;

namespace Ui {
class VerticalLayout;
class FlatLabel;
template <typename Widget>
class SlideWrap;
} // namespace Ui

namespace Info {
namespace Profile {
class Button;
} // namespace Profile
} // namespace Info

namespace Passport {

class PanelController;
class ScanButton;
struct ScanInfo;

class EditScans : public Ui::RpWidget {
public:
	EditScans(
		QWidget *parent,
		not_null<PanelController*> controller,
		const QString &header,
		std::vector<ScanInfo> &&files,
		std::unique_ptr<ScanInfo> &&selfie);

	static void ChooseScan(base::lambda<void(QByteArray&&)> callback);

private:
	void setupContent(const QString &header);
	void chooseScan();
	void chooseSelfie();
	void updateScan(ScanInfo &&info);
	void pushScan(const ScanInfo &info);
	void createSelfieRow(const ScanInfo &info);
	base::unique_qptr<Ui::SlideWrap<ScanButton>> createScan(
		not_null<Ui::VerticalLayout*> parent,
		const ScanInfo &info,
		const QString &name);

	rpl::producer<QString> uploadButtonText() const;

	not_null<PanelController*> _controller;
	std::vector<ScanInfo> _files;
	std::unique_ptr<ScanInfo> _selfie;

	object_ptr<Ui::VerticalLayout> _content;
	QPointer<Ui::SlideWrap<BoxContentDivider>> _divider;
	QPointer<Ui::SlideWrap<Ui::FlatLabel>> _header;
	QPointer<Ui::VerticalLayout> _wrap;
	std::vector<base::unique_qptr<Ui::SlideWrap<ScanButton>>> _rows;
	QPointer<Info::Profile::Button> _upload;
	rpl::event_stream<rpl::producer<QString>> _uploadTexts;

	QPointer<Ui::SlideWrap<Ui::FlatLabel>> _selfieHeader;
	QPointer<Ui::VerticalLayout> _selfieWrap;
	base::unique_qptr<Ui::SlideWrap<ScanButton>> _selfieRow;
	QPointer<Info::Profile::Button> _selfieUpload;

};

} // namespace Passport