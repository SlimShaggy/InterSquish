// ************************************************************************ //
// WARNING                                                                  //
// -------                                                                  //
// The types declared in this file were generated from data read from a     //
// Type Library. If this type library is explicitly or indirectly (via      //
// another type library referring to this type library) re-imported, or the //
// 'Refresh' command of the Type Library Editor activated while editing the //
// Type Library, the contents of this file will be regenerated and all      //
// manual modifications will be lost.                                       //
// ************************************************************************ //

// C++ TLBWRTR : $Revision:   1.96.1.27  $
// File generated on 14.04.99 20:36:37 from Type Library described below.

// ************************************************************************ //
// Type Lib: D:\Program Files\Microsoft Office\Office\EXCEL8.OLB
// IID\LCID: {00020813-0000-0000-C000-000000000046}\0
// Helpfile: D:\Program Files\Microsoft Office\Office\VBAXL8.HLP
// DepndLst: 
//   (1) v2.0 Office, (D:\Program Files\Microsoft Office\Office\MSO97.DLL)
//   (2) v2.0 stdole, (D:\WINNT4\System32\STDOLE2.TLB)
//   (3) v5.0 VBIDE, (D:\Program Files\Common Files\Microsoft Shared\VBA\VBEEXT1.OLB)
//   (4) v4.0 StdVCL, (D:\WINNT4\System32\STDVCL40.DLL)
// ************************************************************************ //
#ifndef   __Excel__h__
#define   __Excel_consts_h__

#pragma option push -b -w-inl

#include <vcl/utilcls.h>
#if !defined(__UTILCLS_H_VERSION) || (__UTILCLS_H_VERSION < 0x0101)
#error "This file requires an newer version of the header file UTILCLS.H"
#endif

//#include <olectl.h>
//#include <ocidl.h>


// *********************************************************************//
// Forward reference of some VCL types (to avoid including STDVCL.HPP)  //
// *********************************************************************//
namespace Stdvcl {class IStrings; class IStringsDisp;}
using namespace Stdvcl;

namespace Excel_tlb
{

// *********************************************************************//
// HelpString: Microsoft Excel 8.0 Object Library
// Version:    1.2
// *********************************************************************//



// *********************************************************************//
// Forward declaration of types defined in TypeLibrary                  //
// *********************************************************************//
enum      Constants;
enum      XlCreator;
enum      XlChartGallery;
enum      XlColorIndex;
enum      XlEndStyleCap;
enum      XlRowCol;
enum      XlScaleType;
enum      XlDataSeriesType;
enum      XlAxisCrosses;
enum      XlAxisGroup;
enum      XlBackground;
enum      XlWindowState;
enum      XlAxisType;
enum      XlArrowHeadLength;
enum      XlVAlign;
enum      XlTickMark;
enum      XlErrorBarDirection;
enum      XlErrorBarInclude;
enum      XlDisplayBlanksAs;
enum      XlArrowHeadStyle;
enum      XlArrowHeadWidth;
enum      XlHAlign;
enum      XlTickLabelPosition;
enum      XlLegendPosition;
enum      XlChartPictureType;
enum      XlChartPicturePlacement;
enum      XlOrientation;
enum      XlTickLabelOrientation;
enum      XlBorderWeight;
enum      XlDataSeriesDate;
enum      XlUnderlineStyle;
enum      XlErrorBarType;
enum      XlTrendlineType;
enum      XlLineStyle;
enum      XlDataLabelsType;
enum      XlMarkerStyle;
enum      XlPictureConvertorType;
enum      XlPattern;
enum      XlChartSplitType;
enum      XlDataLabelPosition;
enum      XlTimeUnit;
enum      XlCategoryType;
enum      XlBarShape;
enum      XlChartType;
enum      XlChartItem;
enum      XlSizeRepresents;
enum      XlInsertShiftDirection;
enum      XlDeleteShiftDirection;
enum      XlDirection;
enum      XlConsolidationFunction;
enum      XlSheetType;
enum      XlLocationInTable;
enum      XlFindLookIn;
enum      XlWindowType;
enum      XlPivotFieldDataType;
enum      XlCopyPictureFormat;
enum      XlPivotTableSourceType;
enum      XlReferenceStyle;
enum      XlMSApplication;
enum      XlMouseButton;
enum      XlCutCopyMode;
enum      XlFillWith;
enum      XlFilterAction;
enum      XlOrder;
enum      XlLinkType;
enum      XlApplyNamesOrder;
enum      XlEnableCancelKey;
enum      XlPageBreak;
enum      XlOLEType;
enum      XlPageOrientation;
enum      XlLinkInfo;
enum      XlCommandUnderlines;
enum      XlOLEVerb;
enum      XlCalculation;
enum      XlFileAccess;
enum      XlEditionType;
enum      XlObjectSize;
enum      XlLookAt;
enum      XlMailSystem;
enum      XlLinkInfoType;
enum      XlCVError;
enum      XlEditionFormat;
enum      XlLink;
enum      XlCellType;
enum      XlArrangeStyle;
enum      XlMousePointer;
enum      XlEditionOptionsOption;
enum      XlAutoFillType;
enum      XlAutoFilterOperator;
enum      XlClipboardFormat;
enum      XlFileFormat;
enum      XlApplicationInternational;
enum      XlPageBreakExtent;
enum      XlCellInsertionMode;
enum      XlFormulaLabel;
enum      XlHighlightChangesTime;
enum      XlCommentDisplayMode;
enum      XlFormatConditionType;
enum      XlFormatConditionOperator;
enum      XlEnableSelection;
enum      XlDVType;
enum      XlIMEMode;
enum      XlDVAlertStyle;
enum      XlChartLocation;
enum      XlPaperSize;
enum      XlPasteSpecialOperation;
enum      XlPasteType;
enum      XlPhoneticCharacterType;
enum      XlPhoneticAlignment;
enum      XlPictureAppearance;
enum      XlPivotFieldOrientation;
enum      XlPivotFieldCalculation;
enum      XlPlacement;
enum      XlPlatform;
enum      XlPrintLocation;
enum      XlPriority;
enum      XlPTSelectionMode;
enum      XlRangeAutoFormat;
enum      XlReferenceType;
enum      XlRoutingSlipDelivery;
enum      XlRoutingSlipStatus;
enum      XlRunAutoMacro;
enum      XlSaveAction;
enum      XlSaveAsAccessMode;
enum      XlSaveConflictResolution;
enum      XlSearchDirection;
enum      XlSearchOrder;
enum      XlSheetVisibility;
enum      XlSortMethod;
enum      XlSortMethodOld;
enum      XlSortOrder;
enum      XlSortOrientation;
enum      XlSortType;
enum      XlSpecialCellsValue;
enum      XlSubscribeToFormat;
enum      XlSummaryRow;
enum      XlSummaryColumn;
enum      XlSummaryReportType;
enum      XlTabPosition;
enum      XlTextParsingType;
enum      XlTextQualifier;
enum      XlWBATemplate;
enum      XlWindowView;
enum      XlXLMMacroType;
enum      XlYesNoGuess;
enum      XlDisplayShapes;
enum      XlBordersIndex;
enum      XlToolbarProtection;
enum      XlBuiltInDialog;
enum      XlParameterType;
enum      XlParameterDataType;
enum      XlFormControl;
interface DECLSPEC_UUID("{000C0310-0000-0000-C000-000000000046}") Adjustments;
interface DECLSPEC_UUID("{000C0311-0000-0000-C000-000000000046}") CalloutFormat;
interface DECLSPEC_UUID("{000C0312-0000-0000-C000-000000000046}") ColorFormat;
interface DECLSPEC_UUID("{000C0317-0000-0000-C000-000000000046}") LineFormat;
interface DECLSPEC_UUID("{000C0318-0000-0000-C000-000000000046}") ShapeNode;
interface DECLSPEC_UUID("{000C0319-0000-0000-C000-000000000046}") ShapeNodes;
interface DECLSPEC_UUID("{000C031A-0000-0000-C000-000000000046}") PictureFormat;
interface DECLSPEC_UUID("{000C031B-0000-0000-C000-000000000046}") ShadowFormat;
interface DECLSPEC_UUID("{000C031F-0000-0000-C000-000000000046}") TextEffectFormat;
interface DECLSPEC_UUID("{000C0321-0000-0000-C000-000000000046}") ThreeDFormat;
interface DECLSPEC_UUID("{000C0314-0000-0000-C000-000000000046}") FillFormat;
interface DECLSPEC_UUID("{0002084D-0001-0000-C000-000000000046}") IFont;
interface DECLSPEC_UUID("{00020893-0001-0000-C000-000000000046}") IWindow;
interface DECLSPEC_UUID("{00020892-0001-0000-C000-000000000046}") IWindows;
interface DECLSPEC_UUID("{00024413-0001-0000-C000-000000000046}") IAppEvents;
interface DECLSPEC_UUID("{000208D5-0000-0000-C000-000000000046}") _Application;
interface DECLSPEC_UUID("{00020845-0001-0000-C000-000000000046}") IWorksheetFunction;
interface DECLSPEC_UUID("{00020846-0001-0000-C000-000000000046}") IRange;
interface DECLSPEC_UUID("{0002440F-0001-0000-C000-000000000046}") IChartEvents;
interface DECLSPEC_UUID("{000208D6-0000-0000-C000-000000000046}") _Chart;
interface DECLSPEC_UUID("{000208D7-0000-0000-C000-000000000046}") Sheets;
interface DECLSPEC_UUID("{00024402-0001-0000-C000-000000000046}") IVPageBreak;
interface DECLSPEC_UUID("{00024401-0001-0000-C000-000000000046}") IHPageBreak;
interface DECLSPEC_UUID("{00024404-0001-0000-C000-000000000046}") IHPageBreaks;
interface DECLSPEC_UUID("{00024405-0001-0000-C000-000000000046}") IVPageBreaks;
interface DECLSPEC_UUID("{00024407-0001-0000-C000-000000000046}") IRecentFile;
interface DECLSPEC_UUID("{00024406-0001-0000-C000-000000000046}") IRecentFiles;
interface DECLSPEC_UUID("{00024411-0001-0000-C000-000000000046}") IDocEvents;
interface DECLSPEC_UUID("{000208D8-0000-0000-C000-000000000046}") _Worksheet;
interface DECLSPEC_UUID("{00020852-0001-0000-C000-000000000046}") IStyle;
interface DECLSPEC_UUID("{00020853-0001-0000-C000-000000000046}") IStyles;
interface DECLSPEC_UUID("{00020855-0001-0000-C000-000000000046}") IBorders;
interface DECLSPEC_UUID("{000208D9-0000-0000-C000-000000000046}") _Global;
interface DECLSPEC_UUID("{00020857-0001-0000-C000-000000000046}") IAddIn;
interface DECLSPEC_UUID("{00020858-0001-0000-C000-000000000046}") IAddIns;
interface DECLSPEC_UUID("{0002085C-0001-0000-C000-000000000046}") IToolbar;
interface DECLSPEC_UUID("{0002085D-0001-0000-C000-000000000046}") IToolbars;
interface DECLSPEC_UUID("{0002085E-0001-0000-C000-000000000046}") IToolbarButton;
interface DECLSPEC_UUID("{0002085F-0001-0000-C000-000000000046}") IToolbarButtons;
interface DECLSPEC_UUID("{00020860-0001-0000-C000-000000000046}") IAreas;
interface DECLSPEC_UUID("{00024412-0001-0000-C000-000000000046}") IWorkbookEvents;
interface DECLSPEC_UUID("{000208DA-0000-0000-C000-000000000046}") _Workbook;
interface DECLSPEC_UUID("{000208DB-0000-0000-C000-000000000046}") Workbooks;
interface DECLSPEC_UUID("{00020863-0001-0000-C000-000000000046}") IMenuBars;
interface DECLSPEC_UUID("{00020864-0001-0000-C000-000000000046}") IMenuBar;
interface DECLSPEC_UUID("{00020865-0001-0000-C000-000000000046}") IMenus;
interface DECLSPEC_UUID("{00020866-0001-0000-C000-000000000046}") IMenu;
interface DECLSPEC_UUID("{00020867-0001-0000-C000-000000000046}") IMenuItems;
interface DECLSPEC_UUID("{00020868-0001-0000-C000-000000000046}") IMenuItem;
interface DECLSPEC_UUID("{0002086D-0001-0000-C000-000000000046}") ICharts;
interface DECLSPEC_UUID("{0002086F-0001-0000-C000-000000000046}") IDrawingObjects;
interface DECLSPEC_UUID("{0002441C-0001-0000-C000-000000000046}") IPivotCache;
interface DECLSPEC_UUID("{0002441D-0001-0000-C000-000000000046}") IPivotCaches;
interface DECLSPEC_UUID("{0002441E-0001-0000-C000-000000000046}") IPivotFormula;
interface DECLSPEC_UUID("{0002441F-0001-0000-C000-000000000046}") IPivotFormulas;
interface DECLSPEC_UUID("{00020872-0001-0000-C000-000000000046}") IPivotTable;
interface DECLSPEC_UUID("{00020873-0001-0000-C000-000000000046}") IPivotTables;
interface DECLSPEC_UUID("{00020874-0001-0000-C000-000000000046}") IPivotField;
interface DECLSPEC_UUID("{00020875-0001-0000-C000-000000000046}") IPivotFields;
interface DECLSPEC_UUID("{00024420-0001-0000-C000-000000000046}") ICalculatedFields;
interface DECLSPEC_UUID("{00020876-0001-0000-C000-000000000046}") IPivotItem;
interface DECLSPEC_UUID("{00020877-0001-0000-C000-000000000046}") IPivotItems;
interface DECLSPEC_UUID("{00024421-0001-0000-C000-000000000046}") ICalculatedItems;
interface DECLSPEC_UUID("{00020878-0001-0000-C000-000000000046}") ICharacters;
interface DECLSPEC_UUID("{00020879-0001-0000-C000-000000000046}") IDialogs;
interface DECLSPEC_UUID("{0002087A-0001-0000-C000-000000000046}") IDialog;
interface DECLSPEC_UUID("{0002087B-0001-0000-C000-000000000046}") ISoundNote;
interface DECLSPEC_UUID("{0002087D-0001-0000-C000-000000000046}") IButton;
interface DECLSPEC_UUID("{0002087E-0001-0000-C000-000000000046}") IButtons;
interface DECLSPEC_UUID("{0002087F-0001-0000-C000-000000000046}") ICheckBox;
interface DECLSPEC_UUID("{00020880-0001-0000-C000-000000000046}") ICheckBoxes;
interface DECLSPEC_UUID("{00020881-0001-0000-C000-000000000046}") IOptionButton;
interface DECLSPEC_UUID("{00020882-0001-0000-C000-000000000046}") IOptionButtons;
interface DECLSPEC_UUID("{00020883-0001-0000-C000-000000000046}") IEditBox;
interface DECLSPEC_UUID("{00020884-0001-0000-C000-000000000046}") IEditBoxes;
interface DECLSPEC_UUID("{00020885-0001-0000-C000-000000000046}") IScrollBar;
interface DECLSPEC_UUID("{00020886-0001-0000-C000-000000000046}") IScrollBars;
interface DECLSPEC_UUID("{00020887-0001-0000-C000-000000000046}") IListBox;
interface DECLSPEC_UUID("{00020888-0001-0000-C000-000000000046}") IListBoxes;
interface DECLSPEC_UUID("{00020889-0001-0000-C000-000000000046}") IGroupBox;
interface DECLSPEC_UUID("{0002088A-0001-0000-C000-000000000046}") IGroupBoxes;
interface DECLSPEC_UUID("{0002088B-0001-0000-C000-000000000046}") IDropDown;
interface DECLSPEC_UUID("{0002088C-0001-0000-C000-000000000046}") IDropDowns;
interface DECLSPEC_UUID("{0002088D-0001-0000-C000-000000000046}") ISpinner;
interface DECLSPEC_UUID("{0002088E-0001-0000-C000-000000000046}") ISpinners;
interface DECLSPEC_UUID("{0002088F-0001-0000-C000-000000000046}") IDialogFrame;
interface DECLSPEC_UUID("{00020890-0001-0000-C000-000000000046}") ILabel;
interface DECLSPEC_UUID("{00020891-0001-0000-C000-000000000046}") ILabels;
interface DECLSPEC_UUID("{00020894-0001-0000-C000-000000000046}") IPanes;
interface DECLSPEC_UUID("{00020895-0001-0000-C000-000000000046}") IPane;
interface DECLSPEC_UUID("{00020896-0001-0000-C000-000000000046}") IScenarios;
interface DECLSPEC_UUID("{00020897-0001-0000-C000-000000000046}") IScenario;
interface DECLSPEC_UUID("{00020898-0001-0000-C000-000000000046}") IGroupObject;
interface DECLSPEC_UUID("{00020899-0001-0000-C000-000000000046}") IGroupObjects;
interface DECLSPEC_UUID("{0002089A-0001-0000-C000-000000000046}") ILine;
interface DECLSPEC_UUID("{0002089B-0001-0000-C000-000000000046}") ILines;
interface DECLSPEC_UUID("{0002089C-0001-0000-C000-000000000046}") IRectangle;
interface DECLSPEC_UUID("{0002089D-0001-0000-C000-000000000046}") IRectangles;
interface DECLSPEC_UUID("{0002089E-0001-0000-C000-000000000046}") IOval;
interface DECLSPEC_UUID("{0002089F-0001-0000-C000-000000000046}") IOvals;
interface DECLSPEC_UUID("{000208A0-0001-0000-C000-000000000046}") IArc;
interface DECLSPEC_UUID("{000208A1-0001-0000-C000-000000000046}") IArcs;
interface DECLSPEC_UUID("{00024410-0001-0000-C000-000000000046}") IOLEObjectEvents;
interface DECLSPEC_UUID("{000208A2-0001-0000-C000-000000000046}") _IOLEObject;
interface DECLSPEC_UUID("{000208A3-0001-0000-C000-000000000046}") IOLEObjects;
interface DECLSPEC_UUID("{000208A4-0001-0000-C000-000000000046}") ITextBox;
interface DECLSPEC_UUID("{000208A5-0001-0000-C000-000000000046}") ITextBoxes;
interface DECLSPEC_UUID("{000208A6-0001-0000-C000-000000000046}") IPicture;
interface DECLSPEC_UUID("{000208A7-0001-0000-C000-000000000046}") IPictures;
interface DECLSPEC_UUID("{000208A8-0001-0000-C000-000000000046}") IDrawing;
interface DECLSPEC_UUID("{000208A9-0001-0000-C000-000000000046}") IDrawings;
interface DECLSPEC_UUID("{000208AA-0001-0000-C000-000000000046}") IRoutingSlip;
interface DECLSPEC_UUID("{000208AB-0001-0000-C000-000000000046}") IOutline;
interface DECLSPEC_UUID("{000208AD-0001-0000-C000-000000000046}") IModule;
interface DECLSPEC_UUID("{000208AE-0001-0000-C000-000000000046}") IModules;
interface DECLSPEC_UUID("{000208AF-0001-0000-C000-000000000046}") IDialogSheet;
interface DECLSPEC_UUID("{000208B0-0001-0000-C000-000000000046}") IDialogSheets;
interface DECLSPEC_UUID("{000208B1-0001-0000-C000-000000000046}") IWorksheets;
interface DECLSPEC_UUID("{000208B4-0001-0000-C000-000000000046}") IPageSetup;
interface DECLSPEC_UUID("{000208B8-0001-0000-C000-000000000046}") INames;
interface DECLSPEC_UUID("{000208B9-0001-0000-C000-000000000046}") IName;
interface DECLSPEC_UUID("{000208CF-0001-0000-C000-000000000046}") IChartObject;
interface DECLSPEC_UUID("{000208D0-0001-0000-C000-000000000046}") IChartObjects;
interface DECLSPEC_UUID("{000208D1-0001-0000-C000-000000000046}") IMailer;
interface DECLSPEC_UUID("{00024422-0001-0000-C000-000000000046}") ICustomViews;
interface DECLSPEC_UUID("{00024423-0001-0000-C000-000000000046}") ICustomView;
interface DECLSPEC_UUID("{00024424-0001-0000-C000-000000000046}") IFormatConditions;
interface DECLSPEC_UUID("{00024425-0001-0000-C000-000000000046}") IFormatCondition;
interface DECLSPEC_UUID("{00024426-0001-0000-C000-000000000046}") IComments;
interface DECLSPEC_UUID("{00024427-0001-0000-C000-000000000046}") IComment;
interface DECLSPEC_UUID("{0002441B-0001-0000-C000-000000000046}") IRefreshEvents;
interface DECLSPEC_UUID("{00024428-0001-0000-C000-000000000046}") _IQueryTable;
interface DECLSPEC_UUID("{00024429-0001-0000-C000-000000000046}") IQueryTables;
interface DECLSPEC_UUID("{0002442A-0001-0000-C000-000000000046}") IParameter;
interface DECLSPEC_UUID("{0002442B-0001-0000-C000-000000000046}") IParameters;
interface DECLSPEC_UUID("{0002442C-0001-0000-C000-000000000046}") IODBCError;
interface DECLSPEC_UUID("{0002442D-0001-0000-C000-000000000046}") IODBCErrors;
interface DECLSPEC_UUID("{0002442F-0001-0000-C000-000000000046}") IValidation;
interface DECLSPEC_UUID("{00024430-0001-0000-C000-000000000046}") IHyperlinks;
interface DECLSPEC_UUID("{00024431-0001-0000-C000-000000000046}") IHyperlink;
interface DECLSPEC_UUID("{00024432-0001-0000-C000-000000000046}") IAutoFilter;
interface DECLSPEC_UUID("{00024433-0001-0000-C000-000000000046}") IFilters;
interface DECLSPEC_UUID("{00024434-0001-0000-C000-000000000046}") IFilter;
interface DECLSPEC_UUID("{000208D4-0001-0000-C000-000000000046}") IAutoCorrect;
interface DECLSPEC_UUID("{00020854-0001-0000-C000-000000000046}") IBorder;
interface DECLSPEC_UUID("{00020870-0001-0000-C000-000000000046}") IInterior;
interface DECLSPEC_UUID("{00024435-0001-0000-C000-000000000046}") IChartFillFormat;
interface DECLSPEC_UUID("{00024436-0001-0000-C000-000000000046}") IChartColorFormat;
interface DECLSPEC_UUID("{00020848-0001-0000-C000-000000000046}") IAxis;
interface DECLSPEC_UUID("{00020849-0001-0000-C000-000000000046}") IChartTitle;
interface DECLSPEC_UUID("{0002084A-0001-0000-C000-000000000046}") IAxisTitle;
interface DECLSPEC_UUID("{00020859-0001-0000-C000-000000000046}") IChartGroup;
interface DECLSPEC_UUID("{0002085A-0001-0000-C000-000000000046}") IChartGroups;
interface DECLSPEC_UUID("{0002085B-0001-0000-C000-000000000046}") IAxes;
interface DECLSPEC_UUID("{00020869-0001-0000-C000-000000000046}") IPoints;
interface DECLSPEC_UUID("{0002086A-0001-0000-C000-000000000046}") IPoint;
interface DECLSPEC_UUID("{0002086B-0001-0000-C000-000000000046}") ISeries;
interface DECLSPEC_UUID("{0002086C-0001-0000-C000-000000000046}") ISeriesCollection;
interface DECLSPEC_UUID("{000208B2-0001-0000-C000-000000000046}") IDataLabel;
interface DECLSPEC_UUID("{000208B3-0001-0000-C000-000000000046}") IDataLabels;
interface DECLSPEC_UUID("{000208BA-0001-0000-C000-000000000046}") ILegendEntry;
interface DECLSPEC_UUID("{000208BB-0001-0000-C000-000000000046}") ILegendEntries;
interface DECLSPEC_UUID("{000208BC-0001-0000-C000-000000000046}") ILegendKey;
interface DECLSPEC_UUID("{000208BD-0001-0000-C000-000000000046}") ITrendlines;
interface DECLSPEC_UUID("{000208BE-0001-0000-C000-000000000046}") ITrendline;
interface DECLSPEC_UUID("{000208C0-0001-0000-C000-000000000046}") ICorners;
interface DECLSPEC_UUID("{000208C1-0001-0000-C000-000000000046}") ISeriesLines;
interface DECLSPEC_UUID("{000208C2-0001-0000-C000-000000000046}") IHiLoLines;
interface DECLSPEC_UUID("{000208C3-0001-0000-C000-000000000046}") IGridlines;
interface DECLSPEC_UUID("{000208C4-0001-0000-C000-000000000046}") IDropLines;
interface DECLSPEC_UUID("{00024437-0001-0000-C000-000000000046}") ILeaderLines;
interface DECLSPEC_UUID("{000208C5-0001-0000-C000-000000000046}") IUpBars;
interface DECLSPEC_UUID("{000208C6-0001-0000-C000-000000000046}") IDownBars;
interface DECLSPEC_UUID("{000208C7-0001-0000-C000-000000000046}") IFloor;
interface DECLSPEC_UUID("{000208C8-0001-0000-C000-000000000046}") IWalls;
interface DECLSPEC_UUID("{000208C9-0001-0000-C000-000000000046}") ITickLabels;
interface DECLSPEC_UUID("{000208CB-0001-0000-C000-000000000046}") IPlotArea;
interface DECLSPEC_UUID("{000208CC-0001-0000-C000-000000000046}") IChartArea;
interface DECLSPEC_UUID("{000208CD-0001-0000-C000-000000000046}") ILegend;
interface DECLSPEC_UUID("{000208CE-0001-0000-C000-000000000046}") IErrorBars;
interface DECLSPEC_UUID("{00020843-0001-0000-C000-000000000046}") IDataTable;
interface DECLSPEC_UUID("{00024438-0001-0000-C000-000000000046}") IPhonetic;
interface DECLSPEC_UUID("{00024439-0001-0000-C000-000000000046}") IShape;
interface DECLSPEC_UUID("{0002443A-0001-0000-C000-000000000046}") IShapes;
interface DECLSPEC_UUID("{0002443B-0001-0000-C000-000000000046}") IShapeRange;
interface DECLSPEC_UUID("{0002443C-0001-0000-C000-000000000046}") IGroupShapes;
interface DECLSPEC_UUID("{0002443D-0001-0000-C000-000000000046}") ITextFrame;
interface DECLSPEC_UUID("{0002443E-0001-0000-C000-000000000046}") IConnectorFormat;
interface DECLSPEC_UUID("{0002443F-0001-0000-C000-000000000046}") IFreeformBuilder;
interface DECLSPEC_UUID("{00024440-0001-0000-C000-000000000046}") IControlFormat;
interface DECLSPEC_UUID("{00024441-0001-0000-C000-000000000046}") IOLEFormat;
interface DECLSPEC_UUID("{00024442-0001-0000-C000-000000000046}") ILinkFormat;
interface DECLSPEC_UUID("{0002084D-0000-0000-C000-000000000046}") Font;
interface DECLSPEC_UUID("{00020893-0000-0000-C000-000000000046}") Window_;
interface DECLSPEC_UUID("{00020892-0000-0000-C000-000000000046}") Windows;
interface DECLSPEC_UUID("{00024413-0000-0000-C000-000000000046}") AppEvents;
interface DECLSPEC_UUID("{00020845-0000-0000-C000-000000000046}") WorksheetFunction;
interface DECLSPEC_UUID("{00020846-0000-0000-C000-000000000046}") Range;
interface DECLSPEC_UUID("{0002440F-0000-0000-C000-000000000046}") ChartEvents;
interface DECLSPEC_UUID("{00024402-0000-0000-C000-000000000046}") VPageBreak;
interface DECLSPEC_UUID("{00024401-0000-0000-C000-000000000046}") HPageBreak;
interface DECLSPEC_UUID("{00024404-0000-0000-C000-000000000046}") HPageBreaks;
interface DECLSPEC_UUID("{00024405-0000-0000-C000-000000000046}") VPageBreaks;
interface DECLSPEC_UUID("{00024407-0000-0000-C000-000000000046}") RecentFile;
interface DECLSPEC_UUID("{00024406-0000-0000-C000-000000000046}") RecentFiles;
interface DECLSPEC_UUID("{00024411-0000-0000-C000-000000000046}") DocEvents;
interface DECLSPEC_UUID("{00020852-0000-0000-C000-000000000046}") Style;
interface DECLSPEC_UUID("{00020853-0000-0000-C000-000000000046}") Styles;
interface DECLSPEC_UUID("{00020855-0000-0000-C000-000000000046}") Borders;
interface DECLSPEC_UUID("{00020857-0000-0000-C000-000000000046}") AddIn;
interface DECLSPEC_UUID("{00020858-0000-0000-C000-000000000046}") AddIns;
interface DECLSPEC_UUID("{0002085C-0000-0000-C000-000000000046}") Toolbar;
interface DECLSPEC_UUID("{0002085D-0000-0000-C000-000000000046}") Toolbars;
interface DECLSPEC_UUID("{0002085E-0000-0000-C000-000000000046}") ToolbarButton;
interface DECLSPEC_UUID("{0002085F-0000-0000-C000-000000000046}") ToolbarButtons;
interface DECLSPEC_UUID("{00020860-0000-0000-C000-000000000046}") Areas;
interface DECLSPEC_UUID("{00024412-0000-0000-C000-000000000046}") WorkbookEvents;
interface DECLSPEC_UUID("{00020863-0000-0000-C000-000000000046}") MenuBars;
interface DECLSPEC_UUID("{00020864-0000-0000-C000-000000000046}") MenuBar;
interface DECLSPEC_UUID("{00020865-0000-0000-C000-000000000046}") Menus;
interface DECLSPEC_UUID("{00020866-0000-0000-C000-000000000046}") Menu;
interface DECLSPEC_UUID("{00020867-0000-0000-C000-000000000046}") MenuItems;
interface DECLSPEC_UUID("{00020868-0000-0000-C000-000000000046}") MenuItem;
interface DECLSPEC_UUID("{0002086D-0000-0000-C000-000000000046}") Charts;
interface DECLSPEC_UUID("{0002086F-0000-0000-C000-000000000046}") DrawingObjects;
interface DECLSPEC_UUID("{0002441C-0000-0000-C000-000000000046}") PivotCache;
interface DECLSPEC_UUID("{0002441D-0000-0000-C000-000000000046}") PivotCaches;
interface DECLSPEC_UUID("{0002441E-0000-0000-C000-000000000046}") PivotFormula;
interface DECLSPEC_UUID("{0002441F-0000-0000-C000-000000000046}") PivotFormulas;
interface DECLSPEC_UUID("{00020872-0000-0000-C000-000000000046}") PivotTable;
interface DECLSPEC_UUID("{00020873-0000-0000-C000-000000000046}") PivotTables;
interface DECLSPEC_UUID("{00020874-0000-0000-C000-000000000046}") PivotField;
interface DECLSPEC_UUID("{00020875-0000-0000-C000-000000000046}") PivotFields;
interface DECLSPEC_UUID("{00024420-0000-0000-C000-000000000046}") CalculatedFields;
interface DECLSPEC_UUID("{00020876-0000-0000-C000-000000000046}") PivotItem;
interface DECLSPEC_UUID("{00020877-0000-0000-C000-000000000046}") PivotItems;
interface DECLSPEC_UUID("{00024421-0000-0000-C000-000000000046}") CalculatedItems;
interface DECLSPEC_UUID("{00020878-0000-0000-C000-000000000046}") Characters;
interface DECLSPEC_UUID("{00020879-0000-0000-C000-000000000046}") Dialogs;
interface DECLSPEC_UUID("{0002087A-0000-0000-C000-000000000046}") Dialog;
interface DECLSPEC_UUID("{0002087B-0000-0000-C000-000000000046}") SoundNote;
interface DECLSPEC_UUID("{0002087D-0000-0000-C000-000000000046}") Button;
interface DECLSPEC_UUID("{0002087E-0000-0000-C000-000000000046}") Buttons;
interface DECLSPEC_UUID("{0002087F-0000-0000-C000-000000000046}") CheckBox;
interface DECLSPEC_UUID("{00020880-0000-0000-C000-000000000046}") CheckBoxes;
interface DECLSPEC_UUID("{00020881-0000-0000-C000-000000000046}") OptionButton;
interface DECLSPEC_UUID("{00020882-0000-0000-C000-000000000046}") OptionButtons;
interface DECLSPEC_UUID("{00020883-0000-0000-C000-000000000046}") EditBox;
interface DECLSPEC_UUID("{00020884-0000-0000-C000-000000000046}") EditBoxes;
interface DECLSPEC_UUID("{00020885-0000-0000-C000-000000000046}") ScrollBar;
interface DECLSPEC_UUID("{00020886-0000-0000-C000-000000000046}") ScrollBars;
interface DECLSPEC_UUID("{00020887-0000-0000-C000-000000000046}") ListBox;
interface DECLSPEC_UUID("{00020888-0000-0000-C000-000000000046}") ListBoxes;
interface DECLSPEC_UUID("{00020889-0000-0000-C000-000000000046}") GroupBox;
interface DECLSPEC_UUID("{0002088A-0000-0000-C000-000000000046}") GroupBoxes;
interface DECLSPEC_UUID("{0002088B-0000-0000-C000-000000000046}") DropDown;
interface DECLSPEC_UUID("{0002088C-0000-0000-C000-000000000046}") DropDowns;
interface DECLSPEC_UUID("{0002088D-0000-0000-C000-000000000046}") Spinner;
interface DECLSPEC_UUID("{0002088E-0000-0000-C000-000000000046}") Spinners;
interface DECLSPEC_UUID("{0002088F-0000-0000-C000-000000000046}") DialogFrame;
interface DECLSPEC_UUID("{00020890-0000-0000-C000-000000000046}") Label;
interface DECLSPEC_UUID("{00020891-0000-0000-C000-000000000046}") Labels;
interface DECLSPEC_UUID("{00020894-0000-0000-C000-000000000046}") Panes;
interface DECLSPEC_UUID("{00020895-0000-0000-C000-000000000046}") Pane;
interface DECLSPEC_UUID("{00020896-0000-0000-C000-000000000046}") Scenarios;
interface DECLSPEC_UUID("{00020897-0000-0000-C000-000000000046}") Scenario;
interface DECLSPEC_UUID("{00020898-0000-0000-C000-000000000046}") GroupObject;
interface DECLSPEC_UUID("{00020899-0000-0000-C000-000000000046}") GroupObjects;
interface DECLSPEC_UUID("{0002089A-0000-0000-C000-000000000046}") Line;
interface DECLSPEC_UUID("{0002089B-0000-0000-C000-000000000046}") Lines;
interface DECLSPEC_UUID("{0002089C-0000-0000-C000-000000000046}") Rectangle;
interface DECLSPEC_UUID("{0002089D-0000-0000-C000-000000000046}") Rectangles;
interface DECLSPEC_UUID("{0002089E-0000-0000-C000-000000000046}") Oval;
interface DECLSPEC_UUID("{0002089F-0000-0000-C000-000000000046}") Ovals;
interface DECLSPEC_UUID("{000208A0-0000-0000-C000-000000000046}") Arc;
interface DECLSPEC_UUID("{000208A1-0000-0000-C000-000000000046}") Arcs;
interface DECLSPEC_UUID("{00024410-0000-0000-C000-000000000046}") OLEObjectEvents;
interface DECLSPEC_UUID("{000208A2-0000-0000-C000-000000000046}") _OLEObject;
interface DECLSPEC_UUID("{000208A3-0000-0000-C000-000000000046}") OLEObjects;
interface DECLSPEC_UUID("{000208A4-0000-0000-C000-000000000046}") TextBox;
interface DECLSPEC_UUID("{000208A5-0000-0000-C000-000000000046}") TextBoxes;
interface DECLSPEC_UUID("{000208A6-0000-0000-C000-000000000046}") Picture;
interface DECLSPEC_UUID("{000208A7-0000-0000-C000-000000000046}") Pictures;
interface DECLSPEC_UUID("{000208A8-0000-0000-C000-000000000046}") Drawing;
interface DECLSPEC_UUID("{000208A9-0000-0000-C000-000000000046}") Drawings;
interface DECLSPEC_UUID("{000208AA-0000-0000-C000-000000000046}") RoutingSlip;
interface DECLSPEC_UUID("{000208AB-0000-0000-C000-000000000046}") Outline;
interface DECLSPEC_UUID("{000208AD-0000-0000-C000-000000000046}") Module;
interface DECLSPEC_UUID("{000208AE-0000-0000-C000-000000000046}") Modules;
interface DECLSPEC_UUID("{000208AF-0000-0000-C000-000000000046}") DialogSheet;
interface DECLSPEC_UUID("{000208B0-0000-0000-C000-000000000046}") DialogSheets;
interface DECLSPEC_UUID("{000208B1-0000-0000-C000-000000000046}") Worksheets;
interface DECLSPEC_UUID("{000208B4-0000-0000-C000-000000000046}") PageSetup;
interface DECLSPEC_UUID("{000208B8-0000-0000-C000-000000000046}") Names;
interface DECLSPEC_UUID("{000208B9-0000-0000-C000-000000000046}") Name;
interface DECLSPEC_UUID("{000208CF-0000-0000-C000-000000000046}") ChartObject;
interface DECLSPEC_UUID("{000208D0-0000-0000-C000-000000000046}") ChartObjects;
interface DECLSPEC_UUID("{000208D1-0000-0000-C000-000000000046}") Mailer;
interface DECLSPEC_UUID("{00024422-0000-0000-C000-000000000046}") CustomViews;
interface DECLSPEC_UUID("{00024423-0000-0000-C000-000000000046}") CustomView;
interface DECLSPEC_UUID("{00024424-0000-0000-C000-000000000046}") FormatConditions;
interface DECLSPEC_UUID("{00024425-0000-0000-C000-000000000046}") FormatCondition;
interface DECLSPEC_UUID("{00024426-0000-0000-C000-000000000046}") Comments;
interface DECLSPEC_UUID("{00024427-0000-0000-C000-000000000046}") Comment;
interface DECLSPEC_UUID("{0002441B-0000-0000-C000-000000000046}") RefreshEvents;
interface DECLSPEC_UUID("{00024428-0000-0000-C000-000000000046}") _QueryTable;
interface DECLSPEC_UUID("{00024429-0000-0000-C000-000000000046}") QueryTables;
interface DECLSPEC_UUID("{0002442A-0000-0000-C000-000000000046}") Parameter;
interface DECLSPEC_UUID("{0002442B-0000-0000-C000-000000000046}") Parameters;
interface DECLSPEC_UUID("{0002442C-0000-0000-C000-000000000046}") ODBCError;
interface DECLSPEC_UUID("{0002442D-0000-0000-C000-000000000046}") ODBCErrors;
interface DECLSPEC_UUID("{0002442F-0000-0000-C000-000000000046}") Validation;
interface DECLSPEC_UUID("{00024430-0000-0000-C000-000000000046}") Hyperlinks;
interface DECLSPEC_UUID("{00024431-0000-0000-C000-000000000046}") Hyperlink;
interface DECLSPEC_UUID("{00024432-0000-0000-C000-000000000046}") AutoFilter;
interface DECLSPEC_UUID("{00024433-0000-0000-C000-000000000046}") Filters;
interface DECLSPEC_UUID("{00024434-0000-0000-C000-000000000046}") Filter;
interface DECLSPEC_UUID("{000208D4-0000-0000-C000-000000000046}") AutoCorrect;
interface DECLSPEC_UUID("{00020854-0000-0000-C000-000000000046}") Border;
interface DECLSPEC_UUID("{00020870-0000-0000-C000-000000000046}") Interior;
interface DECLSPEC_UUID("{00024435-0000-0000-C000-000000000046}") ChartFillFormat;
interface DECLSPEC_UUID("{00024436-0000-0000-C000-000000000046}") ChartColorFormat;
interface DECLSPEC_UUID("{00020848-0000-0000-C000-000000000046}") Axis;
interface DECLSPEC_UUID("{00020849-0000-0000-C000-000000000046}") ChartTitle;
interface DECLSPEC_UUID("{0002084A-0000-0000-C000-000000000046}") AxisTitle;
interface DECLSPEC_UUID("{00020859-0000-0000-C000-000000000046}") ChartGroup;
interface DECLSPEC_UUID("{0002085A-0000-0000-C000-000000000046}") ChartGroups;
interface DECLSPEC_UUID("{0002085B-0000-0000-C000-000000000046}") Axes;
interface DECLSPEC_UUID("{00020869-0000-0000-C000-000000000046}") Points;
interface DECLSPEC_UUID("{0002086A-0000-0000-C000-000000000046}") Point;
interface DECLSPEC_UUID("{0002086B-0000-0000-C000-000000000046}") Series;
interface DECLSPEC_UUID("{0002086C-0000-0000-C000-000000000046}") SeriesCollection;
interface DECLSPEC_UUID("{000208B2-0000-0000-C000-000000000046}") DataLabel;
interface DECLSPEC_UUID("{000208B3-0000-0000-C000-000000000046}") DataLabels;
interface DECLSPEC_UUID("{000208BA-0000-0000-C000-000000000046}") LegendEntry;
interface DECLSPEC_UUID("{000208BB-0000-0000-C000-000000000046}") LegendEntries;
interface DECLSPEC_UUID("{000208BC-0000-0000-C000-000000000046}") LegendKey;
interface DECLSPEC_UUID("{000208BD-0000-0000-C000-000000000046}") Trendlines;
interface DECLSPEC_UUID("{000208BE-0000-0000-C000-000000000046}") Trendline;
interface DECLSPEC_UUID("{000208C0-0000-0000-C000-000000000046}") Corners;
interface DECLSPEC_UUID("{000208C1-0000-0000-C000-000000000046}") SeriesLines;
interface DECLSPEC_UUID("{000208C2-0000-0000-C000-000000000046}") HiLoLines;
interface DECLSPEC_UUID("{000208C3-0000-0000-C000-000000000046}") Gridlines;
interface DECLSPEC_UUID("{000208C4-0000-0000-C000-000000000046}") DropLines;
interface DECLSPEC_UUID("{00024437-0000-0000-C000-000000000046}") LeaderLines;
interface DECLSPEC_UUID("{000208C5-0000-0000-C000-000000000046}") UpBars;
interface DECLSPEC_UUID("{000208C6-0000-0000-C000-000000000046}") DownBars;
interface DECLSPEC_UUID("{000208C7-0000-0000-C000-000000000046}") Floor;
interface DECLSPEC_UUID("{000208C8-0000-0000-C000-000000000046}") Walls;
interface DECLSPEC_UUID("{000208C9-0000-0000-C000-000000000046}") TickLabels;
interface DECLSPEC_UUID("{000208CB-0000-0000-C000-000000000046}") PlotArea;
interface DECLSPEC_UUID("{000208CC-0000-0000-C000-000000000046}") ChartArea;
interface DECLSPEC_UUID("{000208CD-0000-0000-C000-000000000046}") Legend;
interface DECLSPEC_UUID("{000208CE-0000-0000-C000-000000000046}") ErrorBars;
interface DECLSPEC_UUID("{00020843-0000-0000-C000-000000000046}") DataTable;
interface DECLSPEC_UUID("{00024438-0000-0000-C000-000000000046}") Phonetic;
interface DECLSPEC_UUID("{00024439-0000-0000-C000-000000000046}") Shape;
interface DECLSPEC_UUID("{0002443A-0000-0000-C000-000000000046}") Shapes;
interface DECLSPEC_UUID("{0002443B-0000-0000-C000-000000000046}") ShapeRange;
interface DECLSPEC_UUID("{0002443C-0000-0000-C000-000000000046}") GroupShapes;
interface DECLSPEC_UUID("{0002443D-0000-0000-C000-000000000046}") TextFrame;
interface DECLSPEC_UUID("{0002443E-0000-0000-C000-000000000046}") ConnectorFormat;
interface DECLSPEC_UUID("{0002443F-0000-0000-C000-000000000046}") FreeformBuilder;
interface DECLSPEC_UUID("{00024440-0000-0000-C000-000000000046}") ControlFormat;
interface DECLSPEC_UUID("{00024441-0000-0000-C000-000000000046}") OLEFormat;
interface DECLSPEC_UUID("{00024442-0000-0000-C000-000000000046}") LinkFormat;
interface DECLSPEC_UUID("{0002442E-0001-0000-C000-000000000046}") IDummy;

// *********************************************************************//
// Declaration of CoClasses defined in Type Library                     //
// (NOTE: Here we map each CoClass to its Default Interface)            //
//                                                                      //
// The LIBID_OF_ macro(s) map a LIBID_OF_CoClassName to the GUID of this//
// TypeLibrary. It simplifies the updating of macros when CoClass name  //
// change.                                                              //
// *********************************************************************//
typedef _QueryTable QueryTable;
typedef _Application Application_;
typedef _Chart Chart;
typedef _Worksheet Worksheet;
typedef _Global Global;
typedef _Workbook Workbook;
typedef _OLEObject OLEObject;

#define LIBID_OF_QueryTable (&LIBID_Excel)
#define LIBID_OF_Application_ (&LIBID_Excel)
#define LIBID_OF_Chart (&LIBID_Excel)
#define LIBID_OF_Worksheet (&LIBID_Excel)
#define LIBID_OF_Global (&LIBID_Excel)
#define LIBID_OF_Workbook (&LIBID_Excel)
#define LIBID_OF_OLEObject (&LIBID_Excel)

// *********************************************************************//
// Declaration of Enumerations defined in Type Library                  //
// *********************************************************************//
typedef enum Constants
{
  xlAll = 0xFFFFEFF8, 
  xlAutomatic = 0xFFFFEFF7, 
  xlBoth = 1, 
  xlCenter = 0xFFFFEFF4, 
  xlChecker = 9, 
  xlCircle = 8, 
  xlCorner = 2, 
  xlCrissCross = 16, 
  xlCross = 4, 
  xlDiamond = 2, 
  xlDistributed = 0xFFFFEFEB, 
  xlDoubleAccounting = 5, 
  xlFixedValue = 1, 
  xlFormats = 0xFFFFEFE6, 
  xlGray16 = 17, 
  xlGray8 = 18, 
  xlGrid = 15, 
  xlHigh = 0xFFFFEFE1, 
  xlInside = 2, 
  xlJustify = 0xFFFFEFDE, 
  xlLightDown = 13, 
  xlLightHorizontal = 11, 
  xlLightUp = 14, 
  xlLightVertical = 12, 
  xlLow = 0xFFFFEFDA, 
  xlManual = 0xFFFFEFD9, 
  xlMinusValues = 3, 
  xlModule = 0xFFFFEFD3, 
  xlNextToAxis = 4, 
  xlNone = 0xFFFFEFD2, 
  xlNotes = 0xFFFFEFD0, 
  xlOff = 0xFFFFEFCE, 
  xlOn = 1, 
  xlPercent = 2, 
  xlPlus = 9, 
  xlPlusValues = 2, 
  xlSemiGray75 = 10, 
  xlShowLabel = 4, 
  xlShowLabelAndPercent = 5, 
  xlShowPercent = 3, 
  xlShowValue = 2, 
  xlSimple = 0xFFFFEFC6, 
  xlSingle = 2, 
  xlSingleAccounting = 4, 
  xlSolid = 1, 
  xlSquare = 1, 
  xlStar = 5, 
  xlStError = 4, 
  xlToolbarButton = 2, 
  xlTriangle = 3, 
  xlGray25 = 0xFFFFEFE4, 
  xlGray50 = 0xFFFFEFE3, 
  xlGray75 = 0xFFFFEFE2, 
  xlBottom = 0xFFFFEFF5, 
  xlLeft = 0xFFFFEFDD, 
  xlRight = 0xFFFFEFC8, 
  xlTop = 0xFFFFEFC0, 
  xl3DBar = 0xFFFFEFFD, 
  xl3DSurface = 0xFFFFEFF9, 
  xlBar = 2, 
  xlColumn = 3, 
  xlCombination = 0xFFFFEFF1, 
  xlCustom = 0xFFFFEFEE, 
  xlDefaultAutoFormat = 0xFFFFFFFF, 
  xlMaximum = 2, 
  xlMinimum = 4, 
  xlOpaque = 3, 
  xlTransparent = 2, 
  xlBidi = 0xFFFFEC78, 
  xlLatin = 0xFFFFEC77, 
  xlContext = 0xFFFFEC76, 
  xlLTR = 0xFFFFEC75, 
  xlRTL = 0xFFFFEC74, 
  xlVisualCursor = 2, 
  xlLogicalCursor = 1, 
  xlSystem = 1, 
  xlPartial = 3, 
  xlHindiNumerals = 3, 
  xlBidiCalendar = 3, 
  xlGregorian = 2, 
  xlComplete = 4, 
  xlScale = 3, 
  xlClosed = 3, 
  xlColor1 = 7, 
  xlColor2 = 8, 
  xlColor3 = 9, 
  xlConstants = 2, 
  xlContents = 2, 
  xlBelow = 1, 
  xlCascade = 7, 
  xlCenterAcrossSelection = 7, 
  xlChart4 = 2, 
  xlChartSeries = 17, 
  xlChartShort = 6, 
  xlChartTitles = 18, 
  xlClassic1 = 1, 
  xlClassic2 = 2, 
  xlClassic3 = 3, 
  xl3DEffects1 = 13, 
  xl3DEffects2 = 14, 
  xlAbove = 0, 
  xlAccounting1 = 4, 
  xlAccounting2 = 5, 
  xlAccounting3 = 6, 
  xlAccounting4 = 17, 
  xlAdd = 2, 
  xlDebugCodePane = 13, 
  xlDesktop = 9, 
  xlDirect = 1, 
  xlDivide = 5, 
  xlDoubleClosed = 5, 
  xlDoubleOpen = 4, 
  xlDoubleQuote = 1, 
  xlEntireChart = 20, 
  xlExcelMenus = 1, 
  xlExtended = 3, 
  xlFill = 5, 
  xlFirst = 0, 
  xlFloating = 5, 
  xlFormula = 5, 
  xlGeneral = 1, 
  xlGridline = 22, 
  xlIcons = 1, 
  xlImmediatePane = 12, 
  xlInteger = 2, 
  xlLast = 1, 
  xlLastCell = 11, 
  xlList1 = 10, 
  xlList2 = 11, 
  xlList3 = 12, 
  xlLocalFormat1 = 15, 
  xlLocalFormat2 = 16, 
  xlLong = 3, 
  xlLotusHelp = 2, 
  xlMacrosheetCell = 7, 
  xlMixed = 2, 
  xlMultiply = 4, 
  xlNarrow = 1, 
  xlNoDocuments = 3, 
  xlOpen = 2, 
  xlOutside = 3, 
  xlReference = 4, 
  xlSemiautomatic = 2, 
  xlShort = 1, 
  xlSingleQuote = 2, 
  xlStrict = 2, 
  xlSubtract = 3, 
  xlTextBox = 16, 
  xlTiled = 1, 
  xlTitleBar = 8, 
  xlToolbar = 1, 
  xlVisible = 12, 
  xlWatchPane = 11, 
  xlWide = 3, 
  xlWorkbookTab = 6, 
  xlWorksheet4 = 1, 
  xlWorksheetCell = 3, 
  xlWorksheetShort = 5, 
  xlAllExceptBorders = 6, 
  xlLeftToRight = 2, 
  xlTopToBottom = 1, 
  xlVeryHidden = 2, 
  xlDrawingObject = 14
} Constants;

typedef enum XlCreator
{
  xlCreatorCode = 1480803660
} XlCreator;

typedef enum XlChartGallery
{
  xlBuiltIn = 21, 
  xlUserDefined = 22, 
  xlAnyGallery = 23
} XlChartGallery;

typedef enum XlColorIndex
{
  xlColorIndexAutomatic = 0xFFFFEFF7, 
  xlColorIndexNone = 0xFFFFEFD2
} XlColorIndex;

typedef enum XlEndStyleCap
{
  xlCap = 1, 
  xlNoCap = 2
} XlEndStyleCap;

typedef enum XlRowCol
{
  xlColumns = 2, 
  xlRows = 1
} XlRowCol;

typedef enum XlScaleType
{
  xlScaleLinear = 0xFFFFEFDC, 
  xlScaleLogarithmic = 0xFFFFEFDB
} XlScaleType;

typedef enum XlDataSeriesType
{
  xlAutoFill = 4, 
  xlChronological = 3, 
  xlGrowth = 2, 
  xlDataSeriesLinear = 0xFFFFEFDC
} XlDataSeriesType;

typedef enum XlAxisCrosses
{
  xlAxisCrossesAutomatic = 0xFFFFEFF7, 
  xlAxisCrossesCustom = 0xFFFFEFEE, 
  xlAxisCrossesMaximum = 2, 
  xlAxisCrossesMinimum = 4
} XlAxisCrosses;

typedef enum XlAxisGroup
{
  xlPrimary = 1, 
  xlSecondary = 2
} XlAxisGroup;

typedef enum XlBackground
{
  xlBackgroundAutomatic = 0xFFFFEFF7, 
  xlBackgroundOpaque = 3, 
  xlBackgroundTransparent = 2
} XlBackground;

typedef enum XlWindowState
{
  xlMaximized = 0xFFFFEFD7, 
  xlMinimized = 0xFFFFEFD4, 
  xlNormal = 0xFFFFEFD1
} XlWindowState;

typedef enum XlAxisType
{
  xlCategory = 1, 
  xlSeriesAxis = 3, 
  xlValue = 2
} XlAxisType;

typedef enum XlArrowHeadLength
{
  xlArrowHeadLengthLong = 3, 
  xlArrowHeadLengthMedium = 0xFFFFEFD6, 
  xlArrowHeadLengthShort = 1
} XlArrowHeadLength;

typedef enum XlVAlign
{
  xlVAlignBottom = 0xFFFFEFF5, 
  xlVAlignCenter = 0xFFFFEFF4, 
  xlVAlignDistributed = 0xFFFFEFEB, 
  xlVAlignJustify = 0xFFFFEFDE, 
  xlVAlignTop = 0xFFFFEFC0
} XlVAlign;

typedef enum XlTickMark
{
  xlTickMarkCross = 4, 
  xlTickMarkInside = 2, 
  xlTickMarkNone = 0xFFFFEFD2, 
  xlTickMarkOutside = 3
} XlTickMark;

typedef enum XlErrorBarDirection
{
  xlX = 0xFFFFEFB8, 
  xlY = 1
} XlErrorBarDirection;

typedef enum XlErrorBarInclude
{
  xlErrorBarIncludeBoth = 1, 
  xlErrorBarIncludeMinusValues = 3, 
  xlErrorBarIncludeNone = 0xFFFFEFD2, 
  xlErrorBarIncludePlusValues = 2
} XlErrorBarInclude;

typedef enum XlDisplayBlanksAs
{
  xlInterpolated = 3, 
  xlNotPlotted = 1, 
  xlZero = 2
} XlDisplayBlanksAs;

typedef enum XlArrowHeadStyle
{
  xlArrowHeadStyleClosed = 3, 
  xlArrowHeadStyleDoubleClosed = 5, 
  xlArrowHeadStyleDoubleOpen = 4, 
  xlArrowHeadStyleNone = 0xFFFFEFD2, 
  xlArrowHeadStyleOpen = 2
} XlArrowHeadStyle;

typedef enum XlArrowHeadWidth
{
  xlArrowHeadWidthMedium = 0xFFFFEFD6, 
  xlArrowHeadWidthNarrow = 1, 
  xlArrowHeadWidthWide = 3
} XlArrowHeadWidth;

typedef enum XlHAlign
{
  xlHAlignCenter = 0xFFFFEFF4, 
  xlHAlignCenterAcrossSelection = 7, 
  xlHAlignDistributed = 0xFFFFEFEB, 
  xlHAlignFill = 5, 
  xlHAlignGeneral = 1, 
  xlHAlignJustify = 0xFFFFEFDE, 
  xlHAlignLeft = 0xFFFFEFDD, 
  xlHAlignRight = 0xFFFFEFC8
} XlHAlign;

typedef enum XlTickLabelPosition
{
  xlTickLabelPositionHigh = 0xFFFFEFE1, 
  xlTickLabelPositionLow = 0xFFFFEFDA, 
  xlTickLabelPositionNextToAxis = 4, 
  xlTickLabelPositionNone = 0xFFFFEFD2
} XlTickLabelPosition;

typedef enum XlLegendPosition
{
  xlLegendPositionBottom = 0xFFFFEFF5, 
  xlLegendPositionCorner = 2, 
  xlLegendPositionLeft = 0xFFFFEFDD, 
  xlLegendPositionRight = 0xFFFFEFC8, 
  xlLegendPositionTop = 0xFFFFEFC0
} XlLegendPosition;

typedef enum XlChartPictureType
{
  xlStackScale = 3, 
  xlStack = 2, 
  xlStretch = 1
} XlChartPictureType;

typedef enum XlChartPicturePlacement
{
  xlSides = 1, 
  xlEnd = 2, 
  xlEndSides = 3, 
  xlFront = 4, 
  xlFrontSides = 5, 
  xlFrontEnd = 6, 
  xlAllFaces = 7
} XlChartPicturePlacement;

typedef enum XlOrientation
{
  xlDownward = 0xFFFFEFB6, 
  xlHorizontal = 0xFFFFEFE0, 
  xlUpward = 0xFFFFEFB5, 
  xlVertical = 0xFFFFEFBA
} XlOrientation;

typedef enum XlTickLabelOrientation
{
  xlTickLabelOrientationAutomatic = 0xFFFFEFF7, 
  xlTickLabelOrientationDownward = 0xFFFFEFB6, 
  xlTickLabelOrientationHorizontal = 0xFFFFEFE0, 
  xlTickLabelOrientationUpward = 0xFFFFEFB5, 
  xlTickLabelOrientationVertical = 0xFFFFEFBA
} XlTickLabelOrientation;

typedef enum XlBorderWeight
{
  xlHairline = 1, 
  xlMedium = 0xFFFFEFD6, 
  xlThick = 4, 
  xlThin = 2
} XlBorderWeight;

typedef enum XlDataSeriesDate
{
  xlDay = 1, 
  xlMonth = 3, 
  xlWeekday = 2, 
  xlYear = 4
} XlDataSeriesDate;

typedef enum XlUnderlineStyle
{
  xlUnderlineStyleDouble = 0xFFFFEFE9, 
  xlUnderlineStyleDoubleAccounting = 5, 
  xlUnderlineStyleNone = 0xFFFFEFD2, 
  xlUnderlineStyleSingle = 2, 
  xlUnderlineStyleSingleAccounting = 4
} XlUnderlineStyle;

typedef enum XlErrorBarType
{
  xlErrorBarTypeCustom = 0xFFFFEFEE, 
  xlErrorBarTypeFixedValue = 1, 
  xlErrorBarTypePercent = 2, 
  xlErrorBarTypeStDev = 0xFFFFEFC5, 
  xlErrorBarTypeStError = 4
} XlErrorBarType;

typedef enum XlTrendlineType
{
  xlExponential = 5, 
  xlLinear = 0xFFFFEFDC, 
  xlLogarithmic = 0xFFFFEFDB, 
  xlMovingAvg = 6, 
  xlPolynomial = 3, 
  xlPower = 4
} XlTrendlineType;

typedef enum XlLineStyle
{
  xlContinuous = 1, 
  xlDash = 0xFFFFEFED, 
  xlDashDot = 4, 
  xlDashDotDot = 5, 
  xlDot = 0xFFFFEFEA, 
  xlDouble = 0xFFFFEFE9, 
  xlSlantDashDot = 13, 
  xlLineStyleNone = 0xFFFFEFD2
} XlLineStyle;

typedef enum XlDataLabelsType
{
  xlDataLabelsShowNone = 0xFFFFEFD2, 
  xlDataLabelsShowValue = 2, 
  xlDataLabelsShowPercent = 3, 
  xlDataLabelsShowLabel = 4, 
  xlDataLabelsShowLabelAndPercent = 5, 
  xlDataLabelsShowBubbleSizes = 6
} XlDataLabelsType;

typedef enum XlMarkerStyle
{
  xlMarkerStyleAutomatic = 0xFFFFEFF7, 
  xlMarkerStyleCircle = 8, 
  xlMarkerStyleDash = 0xFFFFEFED, 
  xlMarkerStyleDiamond = 2, 
  xlMarkerStyleDot = 0xFFFFEFEA, 
  xlMarkerStyleNone = 0xFFFFEFD2, 
  xlMarkerStylePicture = 0xFFFFEFCD, 
  xlMarkerStylePlus = 9, 
  xlMarkerStyleSquare = 1, 
  xlMarkerStyleStar = 5, 
  xlMarkerStyleTriangle = 3, 
  xlMarkerStyleX = 0xFFFFEFB8
} XlMarkerStyle;

typedef enum XlPictureConvertorType
{
  xlBMP = 1, 
  xlCGM = 7, 
  xlDRW = 4, 
  xlDXF = 5, 
  xlEPS = 8, 
  xlHGL = 6, 
  xlPCT = 13, 
  xlPCX = 10, 
  xlPIC = 11, 
  xlPLT = 12, 
  xlTIF = 9, 
  xlWMF = 2, 
  xlWPG = 3
} XlPictureConvertorType;

typedef enum XlPattern
{
  xlPatternAutomatic = 0xFFFFEFF7, 
  xlPatternChecker = 9, 
  xlPatternCrissCross = 16, 
  xlPatternDown = 0xFFFFEFE7, 
  xlPatternGray16 = 17, 
  xlPatternGray25 = 0xFFFFEFE4, 
  xlPatternGray50 = 0xFFFFEFE3, 
  xlPatternGray75 = 0xFFFFEFE2, 
  xlPatternGray8 = 18, 
  xlPatternGrid = 15, 
  xlPatternHorizontal = 0xFFFFEFE0, 
  xlPatternLightDown = 13, 
  xlPatternLightHorizontal = 11, 
  xlPatternLightUp = 14, 
  xlPatternLightVertical = 12, 
  xlPatternNone = 0xFFFFEFD2, 
  xlPatternSemiGray75 = 10, 
  xlPatternSolid = 1, 
  xlPatternUp = 0xFFFFEFBE, 
  xlPatternVertical = 0xFFFFEFBA
} XlPattern;

typedef enum XlChartSplitType
{
  xlSplitByPosition = 1, 
  xlSplitByPercentValue = 3, 
  xlSplitByCustomSplit = 4, 
  xlSplitByValue = 2
} XlChartSplitType;

typedef enum XlDataLabelPosition
{
  xlLabelPositionCenter = 0xFFFFEFF4, 
  xlLabelPositionAbove = 0, 
  xlLabelPositionBelow = 1, 
  xlLabelPositionLeft = 0xFFFFEFDD, 
  xlLabelPositionRight = 0xFFFFEFC8, 
  xlLabelPositionOutsideEnd = 2, 
  xlLabelPositionInsideEnd = 3, 
  xlLabelPositionInsideBase = 4, 
  xlLabelPositionBestFit = 5, 
  xlLabelPositionMixed = 6, 
  xlLabelPositionCustom = 7
} XlDataLabelPosition;

typedef enum XlTimeUnit
{
  xlDays = 0, 
  xlMonths = 1, 
  xlYears = 2
} XlTimeUnit;

typedef enum XlCategoryType
{
  xlCategoryScale = 2, 
  xlTimeScale = 3, 
  xlAutomaticScale = 0xFFFFEFF7
} XlCategoryType;

typedef enum XlBarShape
{
  xlBox = 0, 
  xlPyramidToPoint = 1, 
  xlPyramidToMax = 2, 
  xlCylinder = 3, 
  xlConeToPoint = 4, 
  xlConeToMax = 5
} XlBarShape;

typedef enum XlChartType
{
  xlColumnClustered = 51, 
  xlColumnStacked = 52, 
  xlColumnStacked100 = 53, 
  xl3DColumnClustered = 54, 
  xl3DColumnStacked = 55, 
  xl3DColumnStacked100 = 56, 
  xlBarClustered = 57, 
  xlBarStacked = 58, 
  xlBarStacked100 = 59, 
  xl3DBarClustered = 60, 
  xl3DBarStacked = 61, 
  xl3DBarStacked100 = 62, 
  xlLineStacked = 63, 
  xlLineStacked100 = 64, 
  xlLineMarkers = 65, 
  xlLineMarkersStacked = 66, 
  xlLineMarkersStacked100 = 67, 
  xlPieOfPie = 68, 
  xlPieExploded = 69, 
  xl3DPieExploded = 70, 
  xlBarOfPie = 71, 
  xlXYScatterSmooth = 72, 
  xlXYScatterSmoothNoMarkers = 73, 
  xlXYScatterLines = 74, 
  xlXYScatterLinesNoMarkers = 75, 
  xlAreaStacked = 76, 
  xlAreaStacked100 = 77, 
  xl3DAreaStacked = 78, 
  xl3DAreaStacked100 = 79, 
  xlDoughnutExploded = 80, 
  xlRadarMarkers = 81, 
  xlRadarFilled = 82, 
  xlSurface = 83, 
  xlSurfaceWireframe = 84, 
  xlSurfaceTopView = 85, 
  xlSurfaceTopViewWireframe = 86, 
  xlBubble = 15, 
  xlBubble3DEffect = 87, 
  xlStockHLC = 88, 
  xlStockOHLC = 89, 
  xlStockVHLC = 90, 
  xlStockVOHLC = 91, 
  xlCylinderColClustered = 92, 
  xlCylinderColStacked = 93, 
  xlCylinderColStacked100 = 94, 
  xlCylinderBarClustered = 95, 
  xlCylinderBarStacked = 96, 
  xlCylinderBarStacked100 = 97, 
  xlCylinderCol = 98, 
  xlConeColClustered = 99, 
  xlConeColStacked = 100, 
  xlConeColStacked100 = 101, 
  xlConeBarClustered = 102, 
  xlConeBarStacked = 103, 
  xlConeBarStacked100 = 104, 
  xlConeCol = 105, 
  xlPyramidColClustered = 106, 
  xlPyramidColStacked = 107, 
  xlPyramidColStacked100 = 108, 
  xlPyramidBarClustered = 109, 
  xlPyramidBarStacked = 110, 
  xlPyramidBarStacked100 = 111, 
  xlPyramidCol = 112, 
  xl3DColumn = 0xFFFFEFFC, 
  xlLine = 4, 
  xl3DLine = 0xFFFFEFFB, 
  xl3DPie = 0xFFFFEFFA, 
  xlPie = 5, 
  xlXYScatter = 0xFFFFEFB7, 
  xl3DArea = 0xFFFFEFFE, 
  xlArea = 1, 
  xlDoughnut = 0xFFFFEFE8, 
  xlRadar = 0xFFFFEFC9
} XlChartType;

typedef enum XlChartItem
{
  xlDataLabel = 0, 
  xlChartArea = 2, 
  xlSeries = 3, 
  xlChartTitle = 4, 
  xlWalls = 5, 
  xlCorners = 6, 
  xlDataTable = 7, 
  xlTrendline = 8, 
  xlErrorBars = 9, 
  xlXErrorBars = 10, 
  xlYErrorBars = 11, 
  xlLegendEntry = 12, 
  xlLegendKey = 13, 
  xlShape = 14, 
  xlMajorGridlines = 15, 
  xlMinorGridlines = 16, 
  xlAxisTitle = 17, 
  xlUpBars = 18, 
  xlPlotArea = 19, 
  xlDownBars = 20, 
  xlAxis = 21, 
  xlSeriesLines = 22, 
  xlFloor = 23, 
  xlLegend = 24, 
  xlHiLoLines = 25, 
  xlDropLines = 26, 
  xlRadarAxisLabels = 27, 
  xlNothing = 28, 
  xlLeaderLines = 29
} XlChartItem;

typedef enum XlSizeRepresents
{
  xlSizeIsWidth = 2, 
  xlSizeIsArea = 1
} XlSizeRepresents;

typedef enum XlInsertShiftDirection
{
  xlShiftDown = 0xFFFFEFE7, 
  xlShiftToRight = 0xFFFFEFBF
} XlInsertShiftDirection;

typedef enum XlDeleteShiftDirection
{
  xlShiftToLeft = 0xFFFFEFC1, 
  xlShiftUp = 0xFFFFEFBE
} XlDeleteShiftDirection;

typedef enum XlDirection
{
  xlDown = 0xFFFFEFE7, 
  xlToLeft = 0xFFFFEFC1, 
  xlToRight = 0xFFFFEFBF, 
  xlUp = 0xFFFFEFBE
} XlDirection;

typedef enum XlConsolidationFunction
{
  xlAverage = 0xFFFFEFF6, 
  xlCount = 0xFFFFEFF0, 
  xlCountNums = 0xFFFFEFEF, 
  xlMax = 0xFFFFEFD8, 
  xlMin = 0xFFFFEFD5, 
  xlProduct = 0xFFFFEFCB, 
  xlStDev = 0xFFFFEFC5, 
  xlStDevP = 0xFFFFEFC4, 
  xlSum = 0xFFFFEFC3, 
  xlVar = 0xFFFFEFBC, 
  xlVarP = 0xFFFFEFBB
} XlConsolidationFunction;

typedef enum XlSheetType
{
  xlChart = 0xFFFFEFF3, 
  xlDialogSheet = 0xFFFFEFEC, 
  xlExcel4IntlMacroSheet = 4, 
  xlExcel4MacroSheet = 3, 
  xlWorksheet = 0xFFFFEFB9
} XlSheetType;

typedef enum XlLocationInTable
{
  xlColumnHeader = 0xFFFFEFF2, 
  xlColumnItem = 5, 
  xlDataHeader = 3, 
  xlDataItem = 7, 
  xlPageHeader = 2, 
  xlPageItem = 6, 
  xlRowHeader = 0xFFFFEFC7, 
  xlRowItem = 4, 
  xlTableBody = 8
} XlLocationInTable;

typedef enum XlFindLookIn
{
  xlFormulas = 0xFFFFEFE5, 
  xlComments = 0xFFFFEFD0, 
  xlValues = 0xFFFFEFBD
} XlFindLookIn;

typedef enum XlWindowType
{
  xlChartAsWindow = 5, 
  xlChartInPlace = 4, 
  xlClipboard = 3, 
  xlInfo = 0xFFFFEFDF, 
  xlWorkbook = 1
} XlWindowType;

typedef enum XlPivotFieldDataType
{
  xlDate = 2, 
  xlNumber = 0xFFFFEFCF, 
  xlText = 0xFFFFEFC2
} XlPivotFieldDataType;

typedef enum XlCopyPictureFormat
{
  xlBitmap = 2, 
  xlPicture = 0xFFFFEFCD
} XlCopyPictureFormat;

typedef enum XlPivotTableSourceType
{
  xlConsolidation = 3, 
  xlDatabase = 1, 
  xlExternal = 2, 
  xlPivotTable = 0xFFFFEFCC
} XlPivotTableSourceType;

typedef enum XlReferenceStyle
{
  xlA1 = 1, 
  xlR1C1 = 0xFFFFEFCA
} XlReferenceStyle;

typedef enum XlMSApplication
{
  xlMicrosoftAccess = 4, 
  xlMicrosoftFoxPro = 5, 
  xlMicrosoftMail = 3, 
  xlMicrosoftPowerPoint = 2, 
  xlMicrosoftProject = 6, 
  xlMicrosoftSchedulePlus = 7, 
  xlMicrosoftWord = 1
} XlMSApplication;

typedef enum XlMouseButton
{
  xlNoButton = 0, 
  xlPrimaryButton = 1, 
  xlSecondaryButton = 2
} XlMouseButton;

typedef enum XlCutCopyMode
{
  xlCopy = 1, 
  xlCut = 2
} XlCutCopyMode;

typedef enum XlFillWith
{
  xlFillWithAll = 0xFFFFEFF8, 
  xlFillWithContents = 2, 
  xlFillWithFormats = 0xFFFFEFE6
} XlFillWith;

typedef enum XlFilterAction
{
  xlFilterCopy = 2, 
  xlFilterInPlace = 1
} XlFilterAction;

typedef enum XlOrder
{
  xlDownThenOver = 1, 
  xlOverThenDown = 2
} XlOrder;

typedef enum XlLinkType
{
  xlLinkTypeExcelLinks = 1, 
  xlLinkTypeOLELinks = 2
} XlLinkType;

typedef enum XlApplyNamesOrder
{
  xlColumnThenRow = 2, 
  xlRowThenColumn = 1
} XlApplyNamesOrder;

typedef enum XlEnableCancelKey
{
  xlDisabled = 0, 
  xlErrorHandler = 2, 
  xlInterrupt = 1
} XlEnableCancelKey;

typedef enum XlPageBreak
{
  xlPageBreakAutomatic = 0xFFFFEFF7, 
  xlPageBreakManual = 0xFFFFEFD9
} XlPageBreak;

typedef enum XlOLEType
{
  xlOLEControl = 2, 
  xlOLEEmbed = 1, 
  xlOLELink = 0
} XlOLEType;

typedef enum XlPageOrientation
{
  xlLandscape = 2, 
  xlPortrait = 1
} XlPageOrientation;

typedef enum XlLinkInfo
{
  xlEditionDate = 2, 
  xlUpdateState = 1
} XlLinkInfo;

typedef enum XlCommandUnderlines
{
  xlCommandUnderlinesAutomatic = 0xFFFFEFF7, 
  xlCommandUnderlinesOff = 0xFFFFEFCE, 
  xlCommandUnderlinesOn = 1
} XlCommandUnderlines;

typedef enum XlOLEVerb
{
  xlVerbOpen = 2, 
  xlVerbPrimary = 1
} XlOLEVerb;

typedef enum XlCalculation
{
  xlCalculationAutomatic = 0xFFFFEFF7, 
  xlCalculationManual = 0xFFFFEFD9, 
  xlCalculationSemiautomatic = 2
} XlCalculation;

typedef enum XlFileAccess
{
  xlReadOnly = 3, 
  xlReadWrite = 2
} XlFileAccess;

typedef enum XlEditionType
{
  xlPublisher = 1, 
  xlSubscriber = 2
} XlEditionType;

typedef enum XlObjectSize
{
  xlFitToPage = 2, 
  xlFullPage = 3, 
  xlScreenSize = 1
} XlObjectSize;

typedef enum XlLookAt
{
  xlPart = 2, 
  xlWhole = 1
} XlLookAt;

typedef enum XlMailSystem
{
  xlMAPI = 1, 
  xlNoMailSystem = 0, 
  xlPowerTalk = 2
} XlMailSystem;

typedef enum XlLinkInfoType
{
  xlLinkInfoOLELinks = 2, 
  xlLinkInfoPublishers = 5, 
  xlLinkInfoSubscribers = 6
} XlLinkInfoType;

typedef enum XlCVError
{
  xlErrDiv0 = 2007, 
  xlErrNA = 2042, 
  xlErrName = 2029, 
  xlErrNull = 2000, 
  xlErrNum = 2036, 
  xlErrRef = 2023, 
  xlErrValue = 2015
} XlCVError;

typedef enum XlEditionFormat
{
  xlBIFF = 2, 
  xlPICT = 1, 
  xlRTF = 4, 
  xlVALU = 8
} XlEditionFormat;

typedef enum XlLink
{
  xlExcelLinks = 1, 
  xlOLELinks = 2, 
  xlPublishers = 5, 
  xlSubscribers = 6
} XlLink;

typedef enum XlCellType
{
  xlCellTypeBlanks = 4, 
  xlCellTypeConstants = 2, 
  xlCellTypeFormulas = 0xFFFFEFE5, 
  xlCellTypeLastCell = 11, 
  xlCellTypeComments = 0xFFFFEFD0, 
  xlCellTypeVisible = 12, 
  xlCellTypeAllFormatConditions = 0xFFFFEFB4, 
  xlCellTypeSameFormatConditions = 0xFFFFEFB3, 
  xlCellTypeAllValidation = 0xFFFFEFB2, 
  xlCellTypeSameValidation = 0xFFFFEFB1
} XlCellType;

typedef enum XlArrangeStyle
{
  xlArrangeStyleCascade = 7, 
  xlArrangeStyleHorizontal = 0xFFFFEFE0, 
  xlArrangeStyleTiled = 1, 
  xlArrangeStyleVertical = 0xFFFFEFBA
} XlArrangeStyle;

typedef enum XlMousePointer
{
  xlIBeam = 3, 
  xlDefault = 0xFFFFEFD1, 
  xlNorthwestArrow = 1, 
  xlWait = 2
} XlMousePointer;

typedef enum XlEditionOptionsOption
{
  xlAutomaticUpdate = 4, 
  xlCancel = 1, 
  xlChangeAttributes = 6, 
  xlManualUpdate = 5, 
  xlOpenSource = 3, 
  xlSelect = 3, 
  xlSendPublisher = 2, 
  xlUpdateSubscriber = 2
} XlEditionOptionsOption;

typedef enum XlAutoFillType
{
  xlFillCopy = 1, 
  xlFillDays = 5, 
  xlFillDefault = 0, 
  xlFillFormats = 3, 
  xlFillMonths = 7, 
  xlFillSeries = 2, 
  xlFillValues = 4, 
  xlFillWeekdays = 6, 
  xlFillYears = 8, 
  xlGrowthTrend = 10, 
  xlLinearTrend = 9
} XlAutoFillType;

typedef enum XlAutoFilterOperator
{
  xlAnd = 1, 
  xlBottom10Items = 4, 
  xlBottom10Percent = 6, 
  xlOr = 2, 
  xlTop10Items = 3, 
  xlTop10Percent = 5
} XlAutoFilterOperator;

typedef enum XlClipboardFormat
{
  xlClipboardFormatBIFF = 8, 
  xlClipboardFormatBIFF2 = 18, 
  xlClipboardFormatBIFF3 = 20, 
  xlClipboardFormatBIFF4 = 30, 
  xlClipboardFormatBinary = 15, 
  xlClipboardFormatBitmap = 9, 
  xlClipboardFormatCGM = 13, 
  xlClipboardFormatCSV = 5, 
  xlClipboardFormatDIF = 4, 
  xlClipboardFormatDspText = 12, 
  xlClipboardFormatEmbeddedObject = 21, 
  xlClipboardFormatEmbedSource = 22, 
  xlClipboardFormatLink = 11, 
  xlClipboardFormatLinkSource = 23, 
  xlClipboardFormatLinkSourceDesc = 32, 
  xlClipboardFormatMovie = 24, 
  xlClipboardFormatNative = 14, 
  xlClipboardFormatObjectDesc = 31, 
  xlClipboardFormatObjectLink = 19, 
  xlClipboardFormatOwnerLink = 17, 
  xlClipboardFormatPICT = 2, 
  xlClipboardFormatPrintPICT = 3, 
  xlClipboardFormatRTF = 7, 
  xlClipboardFormatScreenPICT = 29, 
  xlClipboardFormatStandardFont = 28, 
  xlClipboardFormatStandardScale = 27, 
  xlClipboardFormatSYLK = 6, 
  xlClipboardFormatTable = 16, 
  xlClipboardFormatText = 0, 
  xlClipboardFormatToolFace = 25, 
  xlClipboardFormatToolFacePICT = 26, 
  xlClipboardFormatVALU = 1, 
  xlClipboardFormatWK1 = 10
} XlClipboardFormat;

typedef enum XlFileFormat
{
  xlAddIn = 18, 
  xlCSV = 6, 
  xlCSVMac = 22, 
  xlCSVMSDOS = 24, 
  xlCSVWindows = 23, 
  xlDBF2 = 7, 
  xlDBF3 = 8, 
  xlDBF4 = 11, 
  xlDIF = 9, 
  xlExcel2 = 16, 
  xlExcel2FarEast = 27, 
  xlExcel3 = 29, 
  xlExcel4 = 33, 
  xlExcel5 = 39, 
  xlExcel7 = 39, 
  xlExcel9795 = 43, 
  xlExcel4Workbook = 35, 
  xlIntlAddIn = 26, 
  xlIntlMacro = 25, 
  xlWorkbookNormal = 0xFFFFEFD1, 
  xlSYLK = 2, 
  xlTemplate = 17, 
  xlCurrentPlatformText = 0xFFFFEFC2, 
  xlTextMac = 19, 
  xlTextMSDOS = 21, 
  xlTextPrinter = 36, 
  xlTextWindows = 20, 
  xlWJ2WD1 = 14, 
  xlWK1 = 5, 
  xlWK1ALL = 31, 
  xlWK1FMT = 30, 
  xlWK3 = 15, 
  xlWK4 = 38, 
  xlWK3FM3 = 32, 
  xlWKS = 4, 
  xlWorks2FarEast = 28, 
  xlWQ1 = 34, 
  xlWJ3 = 40, 
  xlWJ3FJ3 = 41
} XlFileFormat;

typedef enum XlApplicationInternational
{
  xl24HourClock = 33, 
  xl4DigitYears = 43, 
  xlAlternateArraySeparator = 16, 
  xlColumnSeparator = 14, 
  xlCountryCode = 1, 
  xlCountrySetting = 2, 
  xlCurrencyBefore = 37, 
  xlCurrencyCode = 25, 
  xlCurrencyDigits = 27, 
  xlCurrencyLeadingZeros = 40, 
  xlCurrencyMinusSign = 38, 
  xlCurrencyNegative = 28, 
  xlCurrencySpaceBefore = 36, 
  xlCurrencyTrailingZeros = 39, 
  xlDateOrder = 32, 
  xlDateSeparator = 17, 
  xlDayCode = 21, 
  xlDayLeadingZero = 42, 
  xlDecimalSeparator = 3, 
  xlGeneralFormatName = 26, 
  xlHourCode = 22, 
  xlLeftBrace = 12, 
  xlLeftBracket = 10, 
  xlListSeparator = 5, 
  xlLowerCaseColumnLetter = 9, 
  xlLowerCaseRowLetter = 8, 
  xlMDY = 44, 
  xlMetric = 35, 
  xlMinuteCode = 23, 
  xlMonthCode = 20, 
  xlMonthLeadingZero = 41, 
  xlMonthNameChars = 30, 
  xlNoncurrencyDigits = 29, 
  xlNonEnglishFunctions = 34, 
  xlRightBrace = 13, 
  xlRightBracket = 11, 
  xlRowSeparator = 15, 
  xlSecondCode = 24, 
  xlThousandsSeparator = 4, 
  xlTimeLeadingZero = 45, 
  xlTimeSeparator = 18, 
  xlUpperCaseColumnLetter = 7, 
  xlUpperCaseRowLetter = 6, 
  xlWeekdayNameChars = 31, 
  xlYearCode = 19
} XlApplicationInternational;

typedef enum XlPageBreakExtent
{
  xlPageBreakFull = 1, 
  xlPageBreakPartial = 2
} XlPageBreakExtent;

typedef enum XlCellInsertionMode
{
  xlOverwriteCells = 0, 
  xlInsertDeleteCells = 1, 
  xlInsertEntireRows = 2
} XlCellInsertionMode;

typedef enum XlFormulaLabel
{
  xlNoLabels = 0xFFFFEFD2, 
  xlRowLabels = 1, 
  xlColumnLabels = 2, 
  xlMixedLabels = 3
} XlFormulaLabel;

typedef enum XlHighlightChangesTime
{
  xlSinceMyLastSave = 1, 
  xlAllChanges = 2, 
  xlNotYetReviewed = 3
} XlHighlightChangesTime;

typedef enum XlCommentDisplayMode
{
  xlNoIndicator = 0, 
  xlCommentIndicatorOnly = 0xFFFFFFFF, 
  xlCommentAndIndicator = 1
} XlCommentDisplayMode;

typedef enum XlFormatConditionType
{
  xlCellValue = 1, 
  xlExpression = 2
} XlFormatConditionType;

typedef enum XlFormatConditionOperator
{
  xlBetween = 1, 
  xlNotBetween = 2, 
  xlEqual = 3, 
  xlNotEqual = 4, 
  xlGreater = 5, 
  xlLess = 6, 
  xlGreaterEqual = 7, 
  xlLessEqual = 8
} XlFormatConditionOperator;

typedef enum XlEnableSelection
{
  xlNoRestrictions = 0, 
  xlUnlockedCells = 1, 
  xlNoSelection = 0xFFFFEFD2
} XlEnableSelection;

typedef enum XlDVType
{
  xlValidateInputOnly = 0, 
  xlValidateWholeNumber = 1, 
  xlValidateDecimal = 2, 
  xlValidateList = 3, 
  xlValidateDate = 4, 
  xlValidateTime = 5, 
  xlValidateTextLength = 6, 
  xlValidateCustom = 7
} XlDVType;

typedef enum XlIMEMode
{
  xlIMEModeNoControl = 0, 
  xlIMEModeOn = 1, 
  xlIMEModeOff = 2, 
  xlIMEModeDisable = 3, 
  xlIMEModeHiragana = 4, 
  xlIMEModeKatakana = 5, 
  xlIMEModeKatakanaHalf = 6, 
  xlIMEModeAlphaFull = 7, 
  xlIMEModeAlpha = 8, 
  xlIMEModeHangulFull = 9, 
  xlIMEModeHangul = 10
} XlIMEMode;

typedef enum XlDVAlertStyle
{
  xlValidAlertStop = 1, 
  xlValidAlertWarning = 2, 
  xlValidAlertInformation = 3
} XlDVAlertStyle;

typedef enum XlChartLocation
{
  xlLocationAsNewSheet = 1, 
  xlLocationAsObject = 2, 
  xlLocationAutomatic = 3
} XlChartLocation;

typedef enum XlPaperSize
{
  xlPaper10x14 = 16, 
  xlPaper11x17 = 17, 
  xlPaperA3 = 8, 
  xlPaperA4 = 9, 
  xlPaperA4Small = 10, 
  xlPaperA5 = 11, 
  xlPaperB4 = 12, 
  xlPaperB5 = 13, 
  xlPaperCsheet = 24, 
  xlPaperDsheet = 25, 
  xlPaperEnvelope10 = 20, 
  xlPaperEnvelope11 = 21, 
  xlPaperEnvelope12 = 22, 
  xlPaperEnvelope14 = 23, 
  xlPaperEnvelope9 = 19, 
  xlPaperEnvelopeB4 = 33, 
  xlPaperEnvelopeB5 = 34, 
  xlPaperEnvelopeB6 = 35, 
  xlPaperEnvelopeC3 = 29, 
  xlPaperEnvelopeC4 = 30, 
  xlPaperEnvelopeC5 = 28, 
  xlPaperEnvelopeC6 = 31, 
  xlPaperEnvelopeC65 = 32, 
  xlPaperEnvelopeDL = 27, 
  xlPaperEnvelopeItaly = 36, 
  xlPaperEnvelopeMonarch = 37, 
  xlPaperEnvelopePersonal = 38, 
  xlPaperEsheet = 26, 
  xlPaperExecutive = 7, 
  xlPaperFanfoldLegalGerman = 41, 
  xlPaperFanfoldStdGerman = 40, 
  xlPaperFanfoldUS = 39, 
  xlPaperFolio = 14, 
  xlPaperLedger = 4, 
  xlPaperLegal = 5, 
  xlPaperLetter = 1, 
  xlPaperLetterSmall = 2, 
  xlPaperNote = 18, 
  xlPaperQuarto = 15, 
  xlPaperStatement = 6, 
  xlPaperTabloid = 3, 
  xlPaperUser = 256
} XlPaperSize;

typedef enum XlPasteSpecialOperation
{
  xlPasteSpecialOperationAdd = 2, 
  xlPasteSpecialOperationDivide = 5, 
  xlPasteSpecialOperationMultiply = 4, 
  xlPasteSpecialOperationNone = 0xFFFFEFD2, 
  xlPasteSpecialOperationSubtract = 3
} XlPasteSpecialOperation;

typedef enum XlPasteType
{
  xlPasteAll = 0xFFFFEFF8, 
  xlPasteAllExceptBorders = 6, 
  xlPasteFormats = 0xFFFFEFE6, 
  xlPasteFormulas = 0xFFFFEFE5, 
  xlPasteComments = 0xFFFFEFD0, 
  xlPasteValues = 0xFFFFEFBD
} XlPasteType;

typedef enum XlPhoneticCharacterType
{
  xlKatakanaHalf = 0, 
  xlKatakana = 1, 
  xlHiragana = 2, 
  xlNoConversion = 3
} XlPhoneticCharacterType;

typedef enum XlPhoneticAlignment
{
  xlPhoneticAlignNoControl = 0, 
  xlPhoneticAlignLeft = 1, 
  xlPhoneticAlignCenter = 2, 
  xlPhoneticAlignDistributed = 3
} XlPhoneticAlignment;

typedef enum XlPictureAppearance
{
  xlPrinter = 2, 
  xlScreen = 1
} XlPictureAppearance;

typedef enum XlPivotFieldOrientation
{
  xlColumnField = 2, 
  xlDataField = 4, 
  xlHidden = 0, 
  xlPageField = 3, 
  xlRowField = 1
} XlPivotFieldOrientation;

typedef enum XlPivotFieldCalculation
{
  xlDifferenceFrom = 2, 
  xlIndex = 9, 
  xlNoAdditionalCalculation = 0xFFFFEFD1, 
  xlPercentDifferenceFrom = 4, 
  xlPercentOf = 3, 
  xlPercentOfColumn = 7, 
  xlPercentOfRow = 6, 
  xlPercentOfTotal = 8, 
  xlRunningTotal = 5
} XlPivotFieldCalculation;

typedef enum XlPlacement
{
  xlFreeFloating = 3, 
  xlMove = 2, 
  xlMoveAndSize = 1
} XlPlacement;

typedef enum XlPlatform
{
  xlMacintosh = 1, 
  xlMSDOS = 3, 
  xlWindows = 2
} XlPlatform;

typedef enum XlPrintLocation
{
  xlPrintSheetEnd = 1, 
  xlPrintInPlace = 16, 
  xlPrintNoComments = 0xFFFFEFD2
} XlPrintLocation;

typedef enum XlPriority
{
  xlPriorityHigh = 0xFFFFEFE1, 
  xlPriorityLow = 0xFFFFEFDA, 
  xlPriorityNormal = 0xFFFFEFD1
} XlPriority;

typedef enum XlPTSelectionMode
{
  xlLabelOnly = 1, 
  xlDataAndLabel = 0, 
  xlDataOnly = 2, 
  xlOrigin = 3, 
  xlButton = 15, 
  xlBlanks = 4
} XlPTSelectionMode;

typedef enum XlRangeAutoFormat
{
  xlRangeAutoFormat3DEffects1 = 13, 
  xlRangeAutoFormat3DEffects2 = 14, 
  xlRangeAutoFormatAccounting1 = 4, 
  xlRangeAutoFormatAccounting2 = 5, 
  xlRangeAutoFormatAccounting3 = 6, 
  xlRangeAutoFormatAccounting4 = 17, 
  xlRangeAutoFormatClassic1 = 1, 
  xlRangeAutoFormatClassic2 = 2, 
  xlRangeAutoFormatClassic3 = 3, 
  xlRangeAutoFormatColor1 = 7, 
  xlRangeAutoFormatColor2 = 8, 
  xlRangeAutoFormatColor3 = 9, 
  xlRangeAutoFormatList1 = 10, 
  xlRangeAutoFormatList2 = 11, 
  xlRangeAutoFormatList3 = 12, 
  xlRangeAutoFormatLocalFormat1 = 15, 
  xlRangeAutoFormatLocalFormat2 = 16, 
  xlRangeAutoFormatLocalFormat3 = 19, 
  xlRangeAutoFormatLocalFormat4 = 20, 
  xlRangeAutoFormatNone = 0xFFFFEFD2, 
  xlRangeAutoFormatSimple = 0xFFFFEFC6
} XlRangeAutoFormat;

typedef enum XlReferenceType
{
  xlAbsolute = 1, 
  xlAbsRowRelColumn = 2, 
  xlRelative = 4, 
  xlRelRowAbsColumn = 3
} XlReferenceType;

typedef enum XlRoutingSlipDelivery
{
  xlAllAtOnce = 2, 
  xlOneAfterAnother = 1
} XlRoutingSlipDelivery;

typedef enum XlRoutingSlipStatus
{
  xlNotYetRouted = 0, 
  xlRoutingComplete = 2, 
  xlRoutingInProgress = 1
} XlRoutingSlipStatus;

typedef enum XlRunAutoMacro
{
  xlAutoActivate = 3, 
  xlAutoClose = 2, 
  xlAutoDeactivate = 4, 
  xlAutoOpen = 1
} XlRunAutoMacro;

typedef enum XlSaveAction
{
  xlDoNotSaveChanges = 2, 
  xlSaveChanges = 1
} XlSaveAction;

typedef enum XlSaveAsAccessMode
{
  xlExclusive = 3, 
  xlNoChange = 1, 
  xlShared = 2
} XlSaveAsAccessMode;

typedef enum XlSaveConflictResolution
{
  xlLocalSessionChanges = 2, 
  xlOtherSessionChanges = 3, 
  xlUserResolution = 1
} XlSaveConflictResolution;

typedef enum XlSearchDirection
{
  xlNext = 1, 
  xlPrevious = 2
} XlSearchDirection;

typedef enum XlSearchOrder
{
  xlByColumns = 2, 
  xlByRows = 1
} XlSearchOrder;

typedef enum XlSheetVisibility
{
  xlSheetVisible = 0xFFFFFFFF, 
  xlSheetHidden = 0, 
  xlSheetVeryHidden = 2
} XlSheetVisibility;

typedef enum XlSortMethod
{
  xlPinYin = 1, 
  xlStroke = 2
} XlSortMethod;

typedef enum XlSortMethodOld
{
  xlCodePage = 2, 
  xlSyllabary = 1
} XlSortMethodOld;

typedef enum XlSortOrder
{
  xlAscending = 1, 
  xlDescending = 2
} XlSortOrder;

typedef enum XlSortOrientation
{
  xlSortRows = 2, 
  xlSortColumns = 1
} XlSortOrientation;

typedef enum XlSortType
{
  xlSortLabels = 2, 
  xlSortValues = 1
} XlSortType;

typedef enum XlSpecialCellsValue
{
  xlErrors = 16, 
  xlLogical = 4, 
  xlNumbers = 1, 
  xlTextValues = 2
} XlSpecialCellsValue;

typedef enum XlSubscribeToFormat
{
  xlSubscribeToPicture = 0xFFFFEFCD, 
  xlSubscribeToText = 0xFFFFEFC2
} XlSubscribeToFormat;

typedef enum XlSummaryRow
{
  xlSummaryAbove = 0, 
  xlSummaryBelow = 1
} XlSummaryRow;

typedef enum XlSummaryColumn
{
  xlSummaryOnLeft = 0xFFFFEFDD, 
  xlSummaryOnRight = 0xFFFFEFC8
} XlSummaryColumn;

typedef enum XlSummaryReportType
{
  xlSummaryPivotTable = 0xFFFFEFCC, 
  xlStandardSummary = 1
} XlSummaryReportType;

typedef enum XlTabPosition
{
  xlTabPositionFirst = 0, 
  xlTabPositionLast = 1
} XlTabPosition;

typedef enum XlTextParsingType
{
  xlDelimited = 1, 
  xlFixedWidth = 2
} XlTextParsingType;

typedef enum XlTextQualifier
{
  xlTextQualifierDoubleQuote = 1, 
  xlTextQualifierNone = 0xFFFFEFD2, 
  xlTextQualifierSingleQuote = 2
} XlTextQualifier;

typedef enum XlWBATemplate
{
  xlWBATChart = 0xFFFFEFF3, 
  xlWBATExcel4IntlMacroSheet = 4, 
  xlWBATExcel4MacroSheet = 3, 
  xlWBATWorksheet = 0xFFFFEFB9
} XlWBATemplate;

typedef enum XlWindowView
{
  xlNormalView = 1, 
  xlPageBreakPreview = 2
} XlWindowView;

typedef enum XlXLMMacroType
{
  xlCommand = 2, 
  xlFunction = 1, 
  xlNotXLM = 3
} XlXLMMacroType;

typedef enum XlYesNoGuess
{
  xlGuess = 0, 
  xlNo = 2, 
  xlYes = 1
} XlYesNoGuess;

typedef enum XlDisplayShapes
{
  XlDisplayShapes_ = 0xFFFFEFF8,
  xlHide = 3,
  xlPlaceholders = 2
} XlDisplayShapes;

typedef enum XlBordersIndex
{
  xlInsideHorizontal = 12,
  xlInsideVertical = 11,
  xlDiagonalDown = 5,
  xlDiagonalUp = 6,
  xlEdgeBottom = 9,
  xlEdgeLeft = 7,
  xlEdgeRight = 10, 
  xlEdgeTop = 8
} XlBordersIndex;

typedef enum XlToolbarProtection
{
  xlNoButtonChanges = 1, 
  xlNoChanges = 4, 
  xlNoDockingChanges = 3, 
  xlToolbarProtectionNone = 0xFFFFEFD1, 
  xlNoShapeChanges = 2
} XlToolbarProtection;

typedef enum XlBuiltInDialog
{
  xlDialogOpen = 1, 
  xlDialogOpenLinks = 2, 
  xlDialogSaveAs = 5, 
  xlDialogFileDelete = 6, 
  xlDialogPageSetup = 7, 
  xlDialogPrint = 8, 
  xlDialogPrinterSetup = 9, 
  xlDialogArrangeAll = 12, 
  xlDialogWindowSize = 13, 
  xlDialogWindowMove = 14, 
  xlDialogRun = 17, 
  xlDialogSetPrintTitles = 23, 
  xlDialogFont = 26, 
  xlDialogDisplay = 27, 
  xlDialogProtectDocument = 28, 
  xlDialogCalculation = 32, 
  xlDialogExtract = 35, 
  xlDialogDataDelete = 36, 
  xlDialogSort = 39, 
  xlDialogDataSeries = 40, 
  xlDialogTable = 41, 
  xlDialogFormatNumber = 42, 
  xlDialogAlignment = 43, 
  xlDialogStyle = 44, 
  xlDialogBorder = 45, 
  xlDialogCellProtection = 46, 
  xlDialogColumnWidth = 47, 
  xlDialogClear = 52, 
  xlDialogPasteSpecial = 53, 
  xlDialogEditDelete = 54, 
  xlDialogInsert = 55, 
  xlDialogPasteNames = 58, 
  xlDialogDefineName = 61, 
  xlDialogCreateNames = 62, 
  xlDialogFormulaGoto = 63, 
  xlDialogFormulaFind = 64, 
  xlDialogGalleryArea = 67, 
  xlDialogGalleryBar = 68, 
  xlDialogGalleryColumn = 69, 
  xlDialogGalleryLine = 70, 
  xlDialogGalleryPie = 71, 
  xlDialogGalleryScatter = 72, 
  xlDialogCombination = 73, 
  xlDialogGridlines = 76, 
  xlDialogAxes = 78, 
  xlDialogAttachText = 80, 
  xlDialogPatterns = 84, 
  xlDialogMainChart = 85, 
  xlDialogOverlay = 86, 
  xlDialogScale = 87, 
  xlDialogFormatLegend = 88, 
  xlDialogFormatText = 89, 
  xlDialogParse = 91, 
  xlDialogUnhide = 94, 
  xlDialogWorkspace = 95, 
  xlDialogActivate = 103, 
  xlDialogCopyPicture = 108, 
  xlDialogDeleteName = 110, 
  xlDialogDeleteFormat = 111, 
  xlDialogNew = 119, 
  xlDialogRowHeight = 127, 
  xlDialogFormatMove = 128, 
  xlDialogFormatSize = 129, 
  xlDialogFormulaReplace = 130, 
  xlDialogSelectSpecial = 132, 
  xlDialogApplyNames = 133, 
  xlDialogReplaceFont = 134, 
  xlDialogSplit = 137, 
  xlDialogOutline = 142, 
  xlDialogSaveWorkbook = 145, 
  xlDialogCopyChart = 147, 
  xlDialogFormatFont = 150, 
  xlDialogNote = 154, 
  xlDialogSetUpdateStatus = 159, 
  xlDialogColorPalette = 161, 
  xlDialogChangeLink = 166, 
  xlDialogAppMove = 170, 
  xlDialogAppSize = 171, 
  xlDialogMainChartType = 185, 
  xlDialogOverlayChartType = 186, 
  xlDialogOpenMail = 188, 
  xlDialogSendMail = 189, 
  xlDialogStandardFont = 190, 
  xlDialogConsolidate = 191, 
  xlDialogSortSpecial = 192, 
  xlDialogGallery3dArea = 193, 
  xlDialogGallery3dColumn = 194, 
  xlDialogGallery3dLine = 195, 
  xlDialogGallery3dPie = 196, 
  xlDialogView3d = 197, 
  xlDialogGoalSeek = 198, 
  xlDialogWorkgroup = 199, 
  xlDialogFillGroup = 200, 
  xlDialogUpdateLink = 201, 
  xlDialogPromote = 202, 
  xlDialogDemote = 203, 
  xlDialogShowDetail = 204, 
  xlDialogObjectProperties = 207, 
  xlDialogSaveNewObject = 208, 
  xlDialogApplyStyle = 212, 
  xlDialogAssignToObject = 213, 
  xlDialogObjectProtection = 214, 
  xlDialogCreatePublisher = 217, 
  xlDialogSubscribeTo = 218, 
  xlDialogShowToolbar = 220, 
  xlDialogPrintPreview = 222, 
  xlDialogEditColor = 223, 
  xlDialogFormatMain = 225, 
  xlDialogFormatOverlay = 226, 
  xlDialogEditSeries = 228, 
  xlDialogDefineStyle = 229, 
  xlDialogGalleryRadar = 249, 
  xlDialogEditionOptions = 251, 
  xlDialogZoom = 256, 
  xlDialogInsertObject = 259, 
  xlDialogSize = 261, 
  xlDialogMove = 262, 
  xlDialogFormatAuto = 269, 
  xlDialogGallery3dBar = 272, 
  xlDialogGallery3dSurface = 273, 
  xlDialogCustomizeToolbar = 276, 
  xlDialogWorkbookAdd = 281, 
  xlDialogWorkbookMove = 282, 
  xlDialogWorkbookCopy = 283, 
  xlDialogWorkbookOptions = 284, 
  xlDialogSaveWorkspace = 285, 
  xlDialogChartWizard = 288, 
  xlDialogAssignToTool = 293, 
  xlDialogPlacement = 300, 
  xlDialogFillWorkgroup = 301, 
  xlDialogWorkbookNew = 302, 
  xlDialogScenarioCells = 305, 
  xlDialogScenarioAdd = 307, 
  xlDialogScenarioEdit = 308, 
  xlDialogScenarioSummary = 311, 
  xlDialogPivotTableWizard = 312, 
  xlDialogPivotFieldProperties = 313, 
  xlDialogOptionsCalculation = 318, 
  xlDialogOptionsEdit = 319, 
  xlDialogOptionsView = 320, 
  xlDialogAddinManager = 321, 
  xlDialogMenuEditor = 322, 
  xlDialogAttachToolbars = 323, 
  xlDialogOptionsChart = 325, 
  xlDialogVbaInsertFile = 328, 
  xlDialogVbaProcedureDefinition = 330, 
  xlDialogRoutingSlip = 336, 
  xlDialogMailLogon = 339, 
  xlDialogInsertPicture = 342, 
  xlDialogGalleryDoughnut = 344, 
  xlDialogChartTrend = 350, 
  xlDialogWorkbookInsert = 354, 
  xlDialogOptionsTransition = 355, 
  xlDialogOptionsGeneral = 356, 
  xlDialogFilterAdvanced = 370, 
  xlDialogMailNextLetter = 378, 
  xlDialogDataLabel = 379, 
  xlDialogInsertTitle = 380, 
  xlDialogFontProperties = 381, 
  xlDialogMacroOptions = 382, 
  xlDialogWorkbookUnhide = 384, 
  xlDialogWorkbookName = 386, 
  xlDialogGalleryCustom = 388, 
  xlDialogAddChartAutoformat = 390, 
  xlDialogChartAddData = 392, 
  xlDialogTabOrder = 394, 
  xlDialogSubtotalCreate = 398, 
  xlDialogWorkbookTabSplit = 415, 
  xlDialogWorkbookProtect = 417, 
  xlDialogScrollbarProperties = 420, 
  xlDialogPivotShowPages = 421, 
  xlDialogTextToColumns = 422, 
  xlDialogFormatCharttype = 423, 
  xlDialogPivotFieldGroup = 433, 
  xlDialogPivotFieldUngroup = 434, 
  xlDialogCheckboxProperties = 435, 
  xlDialogLabelProperties = 436, 
  xlDialogListboxProperties = 437, 
  xlDialogEditboxProperties = 438, 
  xlDialogOpenText = 441, 
  xlDialogPushbuttonProperties = 445, 
  xlDialogFilter = 447, 
  xlDialogFunctionWizard = 450, 
  xlDialogSaveCopyAs = 456, 
  xlDialogOptionsListsAdd = 458, 
  xlDialogSeriesAxes = 460, 
  xlDialogSeriesX = 461, 
  xlDialogSeriesY = 462, 
  xlDialogErrorbarX = 463, 
  xlDialogErrorbarY = 464, 
  xlDialogFormatChart = 465, 
  xlDialogSeriesOrder = 466, 
  xlDialogMailEditMailer = 470, 
  xlDialogStandardWidth = 472, 
  xlDialogScenarioMerge = 473, 
  xlDialogProperties = 474, 
  xlDialogSummaryInfo = 474, 
  xlDialogFindFile = 475, 
  xlDialogActiveCellFont = 476, 
  xlDialogVbaMakeAddin = 478, 
  xlDialogFileSharing = 481, 
  xlDialogAutoCorrect = 485, 
  xlDialogCustomViews = 493, 
  xlDialogInsertNameLabel = 496, 
  xlDialogSeriesShape = 504, 
  xlDialogChartOptionsDataLabels = 505, 
  xlDialogChartOptionsDataTable = 506, 
  xlDialogSetBackgroundPicture = 509, 
  xlDialogDataValidation = 525, 
  xlDialogChartType = 526, 
  xlDialogChartLocation = 527, 
  xlDialogPhonetic = 538, 
  xlDialogChartSourceData = 541, 
  xlDialogSeriesOptions = 557, 
  xlDialogPivotTableOptions = 567, 
  xlDialogPivotSolveOrder = 568, 
  xlDialogPivotCalculatedField = 570, 
  xlDialogPivotCalculatedItem = 572, 
  xlDialogConditionalFormatting = 583, 
  xlDialogInsertHyperlink = 596, 
  xlDialogProtectSharing = 620
} XlBuiltInDialog;

typedef enum XlParameterType
{
  xlPrompt = 0, 
  xlConstant = 1, 
  xlRange = 2
} XlParameterType;

typedef enum XlParameterDataType
{
  xlParamTypeUnknown = 0, 
  xlParamTypeChar = 1, 
  xlParamTypeNumeric = 2, 
  xlParamTypeDecimal = 3, 
  xlParamTypeInteger = 4, 
  xlParamTypeSmallInt = 5, 
  xlParamTypeFloat = 6, 
  xlParamTypeReal = 7, 
  xlParamTypeDouble = 8, 
  xlParamTypeVarChar = 12, 
  xlParamTypeDate = 9, 
  xlParamTypeTime = 10, 
  xlParamTypeTimestamp = 11, 
  xlParamTypeLongVarChar = 0xFFFFFFFF, 
  xlParamTypeBinary = 0xFFFFFFFE, 
  xlParamTypeVarBinary = 0xFFFFFFFD, 
  xlParamTypeLongVarBinary = 0xFFFFFFFC, 
  xlParamTypeBigInt = 0xFFFFFFFB, 
  xlParamTypeTinyInt = 0xFFFFFFFA, 
  xlParamTypeBit = 0xFFFFFFF9
} XlParameterDataType;

typedef enum XlFormControl
{
  xlButtonControl = 0, 
  xlCheckBox = 1, 
  xlDropDown = 2, 
  xlEditBox = 3, 
  xlGroupBox = 4, 
  xlLabel = 5, 
  xlListBox = 6, 
  xlOptionButton = 7, 
  xlScrollBar = 8, 
  xlSpinner = 9
} XlFormControl;


};     // namespace Excel_tlb

#if !defined(NO_IMPLICIT_NAMESPACE_USE)
using  namespace Excel_tlb;
#endif

#pragma option pop

#endif // __Excel_consts_h__
